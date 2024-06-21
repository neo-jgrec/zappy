import Fastify from 'fastify';
import { createServer } from 'http';
import { WebSocketServer } from 'ws';
import net from 'net';
import dotenv from 'dotenv';

dotenv.config();
const port = process.env.PORT || 3000;
const tcpPort = process.env.TCP_PORT || 4000;
const tcpHost = process.env.TCP_HOST || 'localhost';

const fastify = Fastify({
  logger: true
});

const server = createServer(fastify.server);

const wss = new WebSocketServer({ server });

let tcpClient = null;

const connectToTcpServer = () => {
    tcpClient = new net.Socket();

    tcpClient.connect(tcpPort, tcpHost, () => {
        console.log(`Connected to TCP server at ${tcpHost}:${tcpPort}`);
        tcpClient.write('GRAPHIC\n');
    });

    tcpClient.on('data', (data) => {
        console.log(`Received data from TCP server: ${data}`);
        if (wss.clients.size > 0) {
            wss.clients.forEach((client) => {
                if (client.readyState === WebSocketServer.OPEN) {
                    client.send(data);
                }
            });
        }
        console.log('Data sent to WS clients');
    });

    tcpClient.on('close', () => {
        console.log('Connection to TCP server closed. Reconnecting...');
        setTimeout(connectToTcpServer, 1000);
    });

    tcpClient.on('error', (err) => {
        console.error(`TCP client error: ${err}`);
    });
};

connectToTcpServer();

wss.on('connection', (ws) => {
    console.log('Client connected');

    ws.on('message', (message) => {
        console.log(`Received message from WS client: ${message}`);
        if (tcpClient && tcpClient.writable) {
            tcpClient.write(message);
        }
    });

    ws.on('close', () => {
        console.log('Client disconnected');
    });
});

const start = async () => {
    try {
        await fastify.listen({ port: port });
    } catch (err) {
        fastify.log.error(err);
        process.exit(1);
    }
};

start();
