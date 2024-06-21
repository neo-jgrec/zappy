import { createContext, useState, useContext, ReactNode } from 'react';
import { io, Socket } from 'socket.io-client';
import { useSnackbar } from './SnackbarContext';
import { useNavigate } from 'react-router-dom';

interface WebSocketContextProps {
    connect: (host: string, port: string) => void;
    sendMessage: (message: string) => void;
    receivedMessages: { [key: string]: string[] };
    host: string | undefined;
    port: string | undefined;
    setHost: (host: string) => void;
    setPort: (port: string) => void;
    socket: Socket | null;
    connectionStatus: string;
}

const WebSocketContext = createContext<WebSocketContextProps | undefined>(undefined);

export const WebSocketProvider = ({ children }: { children: ReactNode }) => {
    const [socket, setSocket] = useState<Socket | null>(null);
    const [receivedMessages, setReceivedMessages] = useState<{ [key: string]: string[] }>({});
    const navigate = useNavigate();

    const [host, setHost] = useState(localStorage.getItem('host') || undefined);
    const [port, setPort] = useState(localStorage.getItem('port') || undefined);

    const { showSnackbar } = useSnackbar();

    const [connectionStatus, setConnectionStatus] = useState('disconnected');

    const connect = (host: string, port: string) => {
        console.log('Connecting to server:', host, port);
        if (!host || !port) {
            showSnackbar({
                title: 'Error',
                subtitle: 'Host and port are required',
                kind: 'error',
                timeout: 5000
            });
            return;
        }

        if (socket) {
            socket.disconnect();
        }

        const url = `http://${host}:${port}`;
        const newSocket = io(url);

        newSocket.on('connect', () => {
            console.log('Socket.io connection opened');
            setSocket(newSocket);
            setHost(host);
            setPort(port);
            localStorage.setItem('host', host);
            localStorage.setItem('port', port);
            setConnectionStatus('connected');
        });

        newSocket.on('message', (data: string) => {
            console.log('Message from server:', data);
            const type = data.split(' ')[0];
            setReceivedMessages(prev => ({
                ...prev,
                [type]: [...(prev[type] || []), data]
            }));
            console.log(receivedMessages);
        });

        newSocket.on('disconnect', () => {
            console.log('Socket.io connection closed');
            setConnectionStatus('disconnected');
            showSnackbar({
                title: 'Connection Closed',
                subtitle: 'Socket.io connection was closed, retrying to connect',
                kind: 'warning',
                timeout: 5000
            });
        });

        newSocket.on('connect_error', () => {
            setConnectionStatus('error');
            showSnackbar({
                title: 'Error',
                subtitle: 'Unable to connect to the server',
                kind: 'error',
                timeout: 5000
            });
            setSocket(null);
            newSocket.disconnect();
            navigate('/prompt');
        });

        setConnectionStatus('connecting');
        setSocket(newSocket);
    };

    const sendMessage = (message: string) => {
        if (socket && socket.connected) {
            socket.emit('message', message);
        } else {
            showSnackbar({
                title: 'Error',
                subtitle: 'Not connected to the server',
                kind: 'error',
                timeout: 5000
            });
        }
    };

    const contextValue: WebSocketContextProps = {
        connect,
        sendMessage,
        receivedMessages,
        host,
        setHost,
        port,
        setPort,
        socket,
        connectionStatus
    };

    return (
        <WebSocketContext.Provider value={contextValue}>
            {children}
        </WebSocketContext.Provider>
    );
};

export const useWebSocket = () => {
    const context = useContext(WebSocketContext);
    if (context === undefined) {
        throw new Error('useWebSocket must be used within a WebSocketProvider');
    }
    return context;
};
