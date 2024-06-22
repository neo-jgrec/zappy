const { Server } = require("socket.io");
const { createServer } = require("http");
const { Socket } = require("net");
const dotenv = require("dotenv");

dotenv.config();

const httpServer = createServer((req, res) => {
    res.setHeader("Access-Control-Allow-Origin", "*");
    res.setHeader("Access-Control-Allow-Methods", "GET, POST");
    res.end("Socket.io server");
});

const io = new Server(httpServer, {
    cors: {
        origin: "*",
        methods: ["GET", "POST"]
    }
});

const createTcpClient = (socket, tcpHost, tcpPort) => {
    const tcpClient = new Socket();
    socket.tcpClient = tcpClient;

    try {
        tcpClient.connect(tcpPort, tcpHost, () => {
            tcpClient.write('GRAPHIC\n');
        });
    } catch (error) {
        console.error(`TCP client connection error: ${error}`);
        socket.emit('tcpError', error);
    }

    tcpClient.on('data', (data) => {
        let messages = data.toString().split('\n');
        messages.forEach((message) => {
            if (message) {
                console.log(message);
                socket.emit('message', message);
            }
        });
    });

    tcpClient.on('close', () => {
        if (socket.connected) {
            setTimeout(() => createTcpClient(socket, tcpHost, tcpPort), 1000);
        }
    });

    tcpClient.on('error', (err) => {
        socket.emit('tcpError', err);
        console.error(`TCP client error: ${err}`);
    });

    socket.on('message', (msg) => {
        console.log(`Received message from WebSocket client: ${msg}`);
        if (tcpClient && tcpClient.writable) {
            if (!msg.endsWith('\n'))
                msg += '\n';
            tcpClient.write(msg);
        } else {
            console.error('TCP client is not connected');
        }
    });

    socket.on('disconnect', () => {
        console.log('Socket.io connection closed');
        tcpClient.end();
    });

    socket.on('error', (err) => {
        console.error(`Socket.io error: ${err}`);
    });
};

io.on('connection', (socket) => {
    socket.on('connectToTcpServer', (data) => {
        const { host, port } = data;
        createTcpClient(socket, host, port);
    });
});

const port = process.env.PORT || 8888;
httpServer.listen(port, () => {
    console.log(`HTTP server and WebSocket server listening on ${port}`);
});
