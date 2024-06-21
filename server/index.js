const Fastify = require('fastify');
const cors = require('@fastify/cors');
const net = require('net');
const dotenv = require('dotenv');
const { Server } = require("socket.io");

dotenv.config();
const port = process.env.PORT || 8888;
const tcpPort = process.env.TCP_PORT || 4000;
const tcpHost = process.env.TCP_HOST || 'localhost';

const fastify = Fastify({ logger: true });

fastify.register(cors, { origin: '*' });

let tcpClient = null;
let tcpData = '';

const connectToTcpServer = () => {
    tcpClient = new net.Socket();

    tcpClient.connect(tcpPort, tcpHost, () => {
        tcpClient.write('GRAPHIC\n');
    });

    tcpClient.on('data', (data) => {
        tcpData += data.toString();
        let messages = data.toString().split('\n');
        messages.forEach((message) => {
            if (message) {
                sendToWebSocketClients(message);
            }
        });
    });

    tcpClient.on('close', () => {
        setTimeout(connectToTcpServer, 1000);
    });

    tcpClient.on('error', (err) => {
        console.error(`TCP client error: ${err}`);
    });
};

const sendToWebSocketClients = (data) => {
    if (io) {
        io.emit('message', data);
    }
};

const io = new Server(fastify.server, {
    cors: {
        origin: true,
        methods: ["GET", "POST"],
        credentials: true
    }
});

io.on('connection', (socket) => {
    socket.emit('message', tcpData);

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
    });

    socket.on('error', (err) => {
        console.error(`Socket.io error: ${err}`);
    });
});

const start = async () => {
    try {
        await fastify.listen({ port: port });
        console.log(`HTTP server and WebSocket server listening on ${port}`);
        connectToTcpServer();
    } catch (err) {
        fastify.log.error(err);
        process.exit(1);
    }
};

start();
