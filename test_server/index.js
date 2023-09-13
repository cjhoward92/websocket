const { WebSocketServer } = require('ws');

const PORT = process.env.PORT || 18080;
const wss = new WebSocketServer({ port: PORT });

wss.on('connection', (ws) => {
   ws.on('message', (data) => {
      console.log('Received', Buffer.from(data).toString());
      ws.send('ack');
   });
   ws.on('error', (err) => {
      console.error('Error', err);
   });
   ws.on('conclude', () => {
      console.log('conclude');
   });
   ws.on('ping', () => {
      console.log('ping');
      ws.send('pong');
   })
   ws.on('pong', () => {
      console.log('pong');
   });
   ws.on('drain', () => {
      console.log('draining connections');
   });
   console.log('Connection initiated');
   ws.send('pong');
});
console.log('Awaiting connection...');