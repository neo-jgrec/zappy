import { createContext, useState, useContext, ReactNode, useRef, useEffect, useCallback } from 'react';
import { io, Socket } from 'socket.io-client';
import { useSnackbar } from './SnackbarContext';
import { useNavigate } from 'react-router-dom';


enum ResourceType {
    food = 'food',
    linemate = 'linemate',
    deraumere = 'deraumere',
    sibur = 'sibur',
    mendiane = 'mendiane',
    phiras = 'phiras',
    thystame = 'thystame'
}

interface Ressources {
    food: number;
    linemate: number;
    deraumere: number;
    sibur: number;
    mendiane: number;
    phiras: number;
    thystame: number;
}

interface Player {
    id: number;
    x: number;
    y: number;
    orientation?: number;
    level?: number;
    team_name?: string;
    resources: Ressources;
    is_dead: boolean;
}

interface ZappyServerData {
    x: number;
    y: number;
    players: Player[];
    foods: { id: number; x: number; y: number }[];
    teams: string[];
}

const initialZappyServerData: ZappyServerData = {
    x: 0,
    y: 0,
    players: [],
    foods: [],
    teams: []
};

interface WebSocketContextProps {
    connect: (host: string, port: string) => void;
    disconnect: () => void;
    sendMessage: (message: string) => void;
    receivedMessages: { [key: string]: { message: string; timestamp: string }[] };
    hundredLastMessages: { message: string; timestamp: string }[];
    allBroadcastMessages: { id: number; message: string; timestamp: string }[];
    host: string | undefined;
    port: string | undefined;
    setHost: (host: string) => void;
    setPort: (port: string) => void;
    socket: Socket | null;
    connectionStatus: string;
    zappyServerData: ZappyServerData;
    tcpPort: string | undefined;
    setTcpPort: (port: string) => void;
    tcpHost: string | undefined;
    setTcpHost: (host: string) => void;
    standAloneConnect: () => void;
    teamScoresState: { [key: string]: { scores: { timestamp: string, value: number }[] } };
}

const WebSocketContext = createContext<WebSocketContextProps | undefined>(undefined);

export const WebSocketProvider = ({ children }: { children: ReactNode }) => {
    const [socket, setSocket] = useState<Socket | null>(null);
    const [receivedMessages, setReceivedMessages] = useState<{ [key: string]: { message: string; timestamp: string }[] }>({});
    const [hundredLastMessages, setHundredLastMessages] = useState<{ message: string; timestamp: string }[]>([]);
    const HundredLastMessagesRef = useRef<{ message: string; timestamp: string }[]>([]);
    const [allBroadcastMessages, setAllBroadcastMessages] = useState<{ id: number; message: string; timestamp: string }[]>([]);
    const AllBroadcastMessagesRef = useRef<{ id: number; message: string; timestamp: string }[]>([]);
    const [zappyServerData, setZappyServerData] = useState<ZappyServerData>(initialZappyServerData);
    const navigate = useNavigate();

    const [host, setHost] = useState(localStorage.getItem('host') || undefined);
    const [port, setPort] = useState(localStorage.getItem('port') || undefined);

    const [tcpHost, setTcpHost] = useState(localStorage.getItem('tcpHost') || undefined);
    const [tcpPort, setTcpPort] = useState(localStorage.getItem('tcpPort') || undefined);

    const { showSnackbar } = useSnackbar();

    const [connectionStatus, setConnectionStatus] = useState('disconnected');

    const [teamScoresState, setTeamScoresState] = useState<{ [key: string]: { scores: { timestamp: string, value: number }[] } }>({});

    const updateScores = useCallback(() => {
      const newTeamScores = { ...teamScoresState };
      let isStateChanged = false;

      zappyServerData.teams.forEach((team) => {
        if (!newTeamScores[team]) {
          newTeamScores[team] = { scores: [] };
          isStateChanged = true;
        }
        const score = zappyServerData.players.reduce((acc, player) => player.team_name === team ? acc + 15 * (player.level ?? 0) + 10 : acc, 0);
        const lastScore = newTeamScores[team].scores[newTeamScores[team].scores.length - 1];
        if (!lastScore || score !== lastScore.value) {
          newTeamScores[team].scores.push({ timestamp: new Date().toISOString(), value: score });
          isStateChanged = true;
        }
      });

      if (isStateChanged) {
        setTeamScoresState(newTeamScores);
      }
    }, [teamScoresState, zappyServerData]);

    useEffect(() => {
      updateScores();
      const intervalId = setInterval(updateScores, 5000);
      return () => clearInterval(intervalId);
    }, [updateScores]);

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
          newSocket.emit('connectToTcpServer', { host: tcpHost, port: tcpPort });
          setTcpHost(tcpHost);
          setTcpPort(tcpPort);
          localStorage.setItem('tcpHost', tcpHost ?? '');
          localStorage.setItem('tcpPort', tcpPort ?? '');
          showSnackbar({
            title: 'Connected to TCP Server',
            subtitle: `Connected to ${tcpHost}:${tcpPort}`,
            kind: 'success',
            timeout: 5000
          });
          newSocket.emit('message', 'msz');
          newSocket.emit('message', 'tna');
        });

        newSocket.on('tcpError', () => {
            console.log('TCP Error');
            showSnackbar({
                title: 'Error',
                subtitle: 'Unable to connect to the TCP server',
                kind: 'error',
                timeout: 5000
            });
            setConnectionStatus('error');
            setSocket(null);
            newSocket.disconnect();
            navigate('/prompt');
            setZappyServerData(initialZappyServerData);
        });

        newSocket.on('message', (data: string) => {
            if (typeof data !== 'string') return;

            const timestamp = new Date().toISOString();

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
                newAllBroadcastMessages.push({ id: parseInt(id), message, timestamp });
                AllBroadcastMessagesRef.current = newAllBroadcastMessages;
                setAllBroadcastMessages(newAllBroadcastMessages);
            }
            if (data.startsWith('ppo')) {
                const [, id, x, y] = data.split(' ');
                setZappyServerData(prevData => ({
                    ...prevData,
                    players: prevData.players.map(player => player.id === parseInt(id) ? {
                        ...player,
                        x: parseInt(x),
                        y: parseInt(y)
                    } : player)
                }));
            }
            if (data.startsWith('tna')) {
                const [, ...team_names] = data.split(' ');
                zappyServerData.teams.push(...team_names);
            }
            if (data.startsWith('pnw')) {
                const [, id, x, y, orientation, level, team_name] = data.split(' ');
                setZappyServerData(prevData => ({
                    ...prevData,
                    players: [...prevData.players, {
                        id: parseInt(id),
                        x: parseInt(x),
                        y: parseInt(y),
                        orientation: parseInt(orientation),
                        level: parseInt(level),
                        team_name,
                        is_dead: false,
                        resources: {
                            food: 0,
                            linemate: 0,
                            deraumere: 0,
                            sibur: 0,
                            mendiane: 0,
                            phiras: 0,
                            thystame: 0
                        }
                    }]
                }));
                newSocket.emit('message', `pin ${id}`);
                showSnackbar({
                    title: 'Trantorian Spawned',
                    subtitle: `Player at position (${x}, ${y}) in team ${team_name}`,
                    kind: 'info',
                    timeout: 5000
                });
            }
            if (data.startsWith('pdi')) {
                const [, id] = data.split(' ');
                setZappyServerData(prevData => ({
                    ...prevData,
                    players: prevData.players.map(player => player.id === parseInt(id) ? {
                        ...player,
                        is_dead: true
                    } : player)
                }));
            }
            if (data.startsWith('pgt')) {
                const [, id, resource] = data.split(' ');
                const resourceType = Object.values(ResourceType).find((type) => type === resource);
                if (resourceType) {
                    setZappyServerData(prevData => ({
                        ...prevData,
                        players: prevData.players.map(player => player.id === parseInt(id) ? {
                            ...player,
                            resources: {
                                ...player.resources,
                                [resourceType]: player.resources[resourceType] + 1
                            }
                        } : player)
                    }));
                }
            }
            if (data.startsWith('pdr')) {
                const [, id, resource] = data.split(' ');
                const resourceType = Object.values(ResourceType).find((type) => type === resource);
                if (resourceType) {
                    setZappyServerData(prevData => ({
                        ...prevData,
                        players: prevData.players.map(player => player.id === parseInt(id) ? {
                            ...player,
                            resources: {
                                ...player.resources,
                                [resourceType]: player.resources[resourceType] - 1
                            }
                        } : player)
                    }));
                }
            }
            if (data.startsWith('plv')) {
                const [, id, level] = data.split(' ');
                setZappyServerData(prevData => ({
                    ...prevData,
                    players: prevData.players.map(player => player.id === parseInt(id) ? {
                        ...player,
                        level: parseInt(level)
                    } : player)
                }));
            }
            if (data.startsWith('pin')) {
                const [, id, , , ...resources] = data.split(' ');
                setZappyServerData(prevData => ({
                    ...prevData,
                    players: prevData.players.map(player => player.id === parseInt(id) ? {
                        ...player,
                        resources: {
                            food: parseInt(resources[0]),
                            linemate: parseInt(resources[1]),
                            deraumere: parseInt(resources[2]),
                            sibur: parseInt(resources[3]),
                            mendiane: parseInt(resources[4]),
                            phiras: parseInt(resources[5]),
                            thystame: parseInt(resources[6])
                        }
                    } : player)
                }));
            }
            if (data.startsWith('bct')) {
                const [, x, y, resources] = data.split(' ');
                const newZappyServerData = { ...zappyServerData };
                newZappyServerData.foods = newZappyServerData.foods.filter(
                    (food) => food.x !== parseInt(x) && food.y !== parseInt(y)
                );
                resources.split(',').forEach((resource, index) => {
                    if (parseInt(resource) > 0) {
                        newZappyServerData.foods.push({ id: index, x: parseInt(x), y: parseInt(y) });
                    }
                });
                setZappyServerData(newZappyServerData);
            }

            const newHundredLastMessages = [...HundredLastMessagesRef.current];
            if (newHundredLastMessages.length >= 30) {
                newHundredLastMessages.shift();
            }
            newHundredLastMessages.push({ message: data, timestamp });
            HundredLastMessagesRef.current = newHundredLastMessages;
            setHundredLastMessages(newHundredLastMessages);

            const newReceivedMessages = { ...receivedMessages };
            if (!newReceivedMessages[data]) newReceivedMessages[data] = [];
            newReceivedMessages[data].push({ message: data, timestamp });
            setReceivedMessages(newReceivedMessages);
        });

        newSocket.on('disconnect', () => {
            setConnectionStatus('disconnected');
            showSnackbar({
                title: 'Connection Closed',
                subtitle: 'Socket.io connection was closed nor the TCP server is not reachable',
                kind: 'warning',
                timeout: 5000
            });
            navigate('/prompt');
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

    const standAloneConnect = () => {
        if (!tcpHost || !tcpPort) {
            showSnackbar({
                title: 'Error',
                subtitle: 'TCP Host and Port are required',
                kind: 'error',
                timeout: 5000
            });
            return;
        }

        if (socket && socket.connected) {
            socket.emit('connectToTcpServer', { host: tcpHost, port: tcpPort });
            setTcpHost(tcpHost);
            setTcpPort(tcpPort);
            localStorage.setItem('tcpHost', tcpHost);
            localStorage.setItem('tcpPort', tcpPort);
            showSnackbar({
                title: 'Connected to TCP Server',
                subtitle: `Connected to ${tcpHost}:${tcpPort}`,
                kind: 'success',
                timeout: 5000
            });
        } else {
            showSnackbar({
                title: 'Error',
                subtitle: 'Not connected to the server',
                kind: 'error',
                timeout: 5000
            });
        }
    };

    useEffect(() => {
        connect(host || '', port || '');
        console.log('Connecting to', host, port);
        return () => {
            disconnect();
        }
    }, []);

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
        zappyServerData,
        tcpHost,
        setTcpHost,
        tcpPort,
        setTcpPort,
        standAloneConnect,
        teamScoresState
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
