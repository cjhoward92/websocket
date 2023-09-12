const { WebSocketServer } = require('ws');

const PORT = process.env.PORT || 18080;
const wss = new WebSocketServer({ port: PORT });

wss.on('connection', (ws) => {
   ws.on('message', (data) => {
      console.log('Received', data);
      ws.send('ack');
   });
   console.log('Connection initiated');
   ws.send('pong');
});
console.log('Awaiting connection...');