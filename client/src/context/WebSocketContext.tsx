import { createContext, useState, useContext, ReactNode, useRef, useEffect } from 'react';
import { io, Socket } from 'socket.io-client';
import { useSnackbar } from './SnackbarContext';
import { useNavigate } from 'react-router-dom';

interface ZappyServerData {
    x: number;
    y: number;
    player_positions: { id: number; x: number; y: number, orientation?: number, level?: number, team_name?: string }[];
    food_positions: { id: number; x: number; y: number }[];
    team_names: string[];
}

const initialZappyServerData: ZappyServerData = {
    x: 0,
    y: 0,
    player_positions: [],
    food_positions: [],
    team_names: []
};

interface WebSocketContextProps {
    connect: (host: string, port: string) => void;
    disconnect: () => void;
    sendMessage: (message: string) => void;
    receivedMessages: { [key: string]: string[] };
    hundredLastMessages: string[];
    allBroadcastMessages: { id: number; message: string }[];
    host: string | undefined;
    port: string | undefined;
    setHost: (host: string) => void;
    setPort: (port: string) => void;
    socket: Socket | null;
    connectionStatus: string;
    zappyServerData: ZappyServerData;
}

const WebSocketContext = createContext<WebSocketContextProps | undefined>(undefined);

export const WebSocketProvider = ({ children }: { children: ReactNode }) => {
    const [socket, setSocket] = useState<Socket | null>(null);
    const [receivedMessages, setReceivedMessages] = useState<{ [key: string]: string[] }>({});
    const [hundredLastMessages, setHundredLastMessages] = useState<string[]>([]);
    const HundredLastMessagesRef = useRef<string[]>([]);
    const [allBroadcastMessages, setAllBroadcastMessages] = useState<{ id: number; message: string }[]>([]);
    const AllBroadcastMessagesRef = useRef<{ id: number; message: string }[]>([]);
    const [zappyServerData, setZappyServerData] = useState<ZappyServerData>(initialZappyServerData);
    const navigate = useNavigate();


    const [host, setHost] = useState(localStorage.getItem('host') || undefined);
    const [port, setPort] = useState(localStorage.getItem('port') || undefined);

    const { showSnackbar } = useSnackbar();

    const [connectionStatus, setConnectionStatus] = useState('disconnected');

    const connect = (host: string, port: string) => {
        showSnackbar({
            title: 'Connecting',
            subtitle: `Connecting to ${host}:${port}...`,
            kind: 'info',
            timeout: 5000
        });
        if (!host || !port) {
            showSnackbar({
                title: 'Error',
                subtitle: 'Host and port are required',
                kind: 'error',
                timeout: 5000
            });
            return;
        }

        const url = `http://${host}:${port}`;
        const newSocket = io(url);

        newSocket.on('connect', () => {
            showSnackbar({
                title: 'Connected',
                subtitle: `Connected to ${host}:${port}`,
                kind: 'success',
                timeout: 5000
            });
            setSocket(newSocket);
            setHost(host);
            setPort(port);
            localStorage.setItem('host', host);
            localStorage.setItem('port', port);
            setConnectionStatus('connected');
            newSocket.emit('message', 'msz');
            newSocket.emit('message', 'tna');
        });

        newSocket.on('message', (data: string) => {
            if (typeof data !== 'string') return;

            if (!data.startsWith('bct')) {
                if (data.startsWith('msz')) {
                    const [, x, y] = data.split(' ');
                    setZappyServerData(prevData => ({
                        ...prevData,
                        x: parseInt(x),
                        y: parseInt(y)
                    }));
                }
                if (data.startsWith('pbc')) {
                    const [, id, message] = data.split(' ');
                    const newAllBroadcastMessages = [...AllBroadcastMessagesRef.current];
                    newAllBroadcastMessages.push({ id: parseInt(id), message });
                    AllBroadcastMessagesRef.current = newAllBroadcastMessages;
                    setAllBroadcastMessages(newAllBroadcastMessages);
                }
                if (data.startsWith('ppo')) {
                    const [, id, x, y] = data.split(' ');
                    setZappyServerData(prevData => ({
                        ...prevData,
                        player_positions: prevData.player_positions.map(player => player.id === parseInt(id) ? {
                            ...player,
                            x: parseInt(x),
                            y: parseInt(y)
                        } : player)
                    }));
                }
                if (data.startsWith('tna')) {
                    const [, ...team_names] = data.split(' ');
                    zappyServerData.team_names.push(...team_names);
                }
                if (data.startsWith('pnw')) {
                    const [, id, x, y, orientation, level, team_name] = data.split(' ');
                    setZappyServerData(prevData => ({
                        ...prevData,
                        player_positions: [...prevData.player_positions, {
                            id: parseInt(id),
                            x: parseInt(x),
                            y: parseInt(y),
                            orientation: parseInt(orientation),
                            level: parseInt(level),
                            team_name
                        }]
                    }));
                }
                if (data.startsWith('pdi')) {
                    const [, id] = data.split(' ');
                    setZappyServerData(prevData => ({
                        ...prevData,
                        player_positions: prevData.player_positions.filter(player => player.id !== parseInt(id))
                    }));
                }
                if (data.startsWith('pgt')) {
                    const [,, resource] = data.split(' ');
                    setZappyServerData(prevData => ({
                        ...prevData,
                        food_positions: prevData.food_positions.filter(
                            (food) => food.id !== parseInt(resource)
                        )
                    }));
                }
                if (data.startsWith('pdr')) {
                    const [,, resource] = data.split(' ');
                    setZappyServerData(prevData => ({
                        ...prevData,
                        food_positions: [...prevData.food_positions, {
                            id: parseInt(resource),
                            x: prevData.player_positions[0].x,
                            y: prevData.player_positions[0].y
                        }]
                    }));
                }
                if (data.startsWith('plv')) {
                    const [, id, level] = data.split(' ');
                    setZappyServerData(prevData => ({
                        ...prevData,
                        player_positions: prevData.player_positions.map(player => player.id === parseInt(id) ? {
                            ...player,
                            level: parseInt(level)
                        } : player)
                    }));
                }
            }
            const newHundredLastMessages = [...HundredLastMessagesRef.current];
            if (newHundredLastMessages.length >= 100) {
                newHundredLastMessages.shift();
            }
            newHundredLastMessages.push(data);
            HundredLastMessagesRef.current = newHundredLastMessages;
            setHundredLastMessages(newHundredLastMessages);

            if (data.startsWith('bct')) {
                const [, x, y, resources] = data.split(' ');
                const newZappyServerData = { ...zappyServerData };
                newZappyServerData.food_positions = newZappyServerData.food_positions.filter(
                    (food) => food.x !== parseInt(x) && food.y !== parseInt(y)
                );
                resources.split(',').forEach((resource, index) => {
                    if (parseInt(resource) > 0) {
                        newZappyServerData.food_positions.push({ id: index, x: parseInt(x), y: parseInt(y) });
                    }
                });
                setZappyServerData(newZappyServerData);
            }

            const newReceivedMessages = { ...receivedMessages };
            if (!newReceivedMessages[data]) newReceivedMessages[data] = [];
            newReceivedMessages[data].push(data);
            setReceivedMessages(newReceivedMessages);
        });

        newSocket.on('disconnect', () => {
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

    const disconnect = () => {
        if (socket) {
            socket.disconnect();
            setSocket(null);
            setConnectionStatus('disconnected');
            setZappyServerData(initialZappyServerData);
        }
    };

    useEffect(() => {
        return () => {
            if (socket) {
                socket.disconnect();
            }
        };
    }, [socket]);

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
        disconnect,
        sendMessage,
        receivedMessages,
        host,
        setHost,
        port,
        setPort,
        socket,
        connectionStatus,
        hundredLastMessages,
        allBroadcastMessages,
        zappyServerData
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
