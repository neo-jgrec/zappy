import Fastify from 'fastify';
import cors from '@fastify/cors';
import { Socket } from 'net';
import { config } from 'dotenv';
import { Server } from "socket.io";

config();
const port = process.env.PORT || 8888;
const tcpPort = process.env.TCP_PORT || 4000;
const tcpHost = process.env.TCP_HOST || 'localhost';

const fastify = Fastify({ logger: true });

fastify.register(cors, { origin: '*' });

const io = new Server(fastify.server, {
    cors: {
        origin: true,
        methods: ["GET", "POST"],
        credentials: true
    }
});

const createTcpClient = (socket) => {
    const tcpClient = new Socket();
    socket.tcpClient = tcpClient;

    tcpClient.connect(tcpPort, tcpHost, () => {
        tcpClient.write('GRAPHIC\n');
    });

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
            setTimeout(() => createTcpClient(socket), 1000);
        }
    });

    tcpClient.on('error', (err) => {
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
    createTcpClient(socket);
});

const start = async () => {
    try {
        await fastify.listen({ port: port });
        console.log(`HTTP server and WebSocket server listening on ${port}`);
    } catch (err) {
        fastify.log.error(err);
        process.exit(1);
    }
};

start();
