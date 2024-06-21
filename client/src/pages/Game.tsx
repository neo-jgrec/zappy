import { useRef, useState, useEffect } from 'react';
import { Layout } from "../components";
import { useWebSocket } from '../context';
import {
  Button,
  TextInput,
  Tile
} from '@carbon/react';
import {
  Send
} from '@carbon/icons-react';

function Game() {
  const canvasRef = useRef(null);
  const [zoom, setZoom] = useState(1);
  const [pan, setPan] = useState({ x: 0, y: 0 });
  const [isPanning, setIsPanning] = useState(false);
  const [startPan, setStartPan] = useState({ x: 0, y: 0 });

  const { hundredLastMessages, allBroadcastMessages } = useWebSocket();

  useEffect(() => {
    const canvas = canvasRef.current as unknown as HTMLCanvasElement;
    const context = canvas?.getContext('2d');

    const draw = () => {
      if (!context || !canvas) return;
      context.clearRect(0, 0, canvas.width, canvas.height);
      context.save();
      context.scale(zoom, zoom);
      context.translate(pan.x / zoom, pan.y / zoom);

      context.fillStyle = 'red';
      context.fillRect(50, 50, 100, 100);

      context.restore();
    };

    draw();
  }, [zoom, pan]);

  const handleWheel = (event: { preventDefault: () => void; deltaY: number; }) => {
    event.preventDefault();
    const scaleAmount = -event.deltaY * 0.01;
    setZoom((prevZoom) => Math.min(Math.max(prevZoom + scaleAmount, 0.5), 3));
  };

  const handleMouseDown = (event: { clientX: number; clientY: number; }) => {
    setIsPanning(true);
    setStartPan({ x: event.clientX - pan.x, y: event.clientY - pan.y });
  };

  const handleMouseMove = (event: { clientX: number; clientY: number; }) => {
    if (isPanning) {
      setPan({ x: event.clientX - startPan.x, y: event.clientY - startPan.y });
    }
  };

  const handleMouseUp = () => {
    setIsPanning(false);
  };

  return (
    <Layout>
      <div className='flex space-x-4'>
        <Tile className='w-full relative w-[85vh] h-[85vh] overflow-hidden bg-blue-900 bg-opacity-5 rounded-xl'>
          <div
            onWheel={handleWheel}
            onMouseDown={handleMouseDown}
            onMouseMove={handleMouseMove}
            onMouseUp={handleMouseUp}
            onMouseLeave={handleMouseUp}
          >
            <canvas
              ref={canvasRef}
              width={384}
              height={384}
              className='absolute top-0 left-0 w-full h-full'
            ></canvas>
          </div>
        </Tile>

        <div className='grid grid-cols-2 gap-4 w-full'>
          <Tile className='p-4' style={{ display: 'flex', flexDirection: 'column', justifyContent: 'flex-end', height: '100%' }}>
            <h2>Game Events</h2>
            <div style={{ flex: '1 1 auto', overflowY: 'auto', display: 'flex', flexDirection: 'column', justifyContent: 'flex-end' }}>
              <ul className='overflow-y-auto'>
                {hundredLastMessages.map((message, index) => (
                  <li key={index} className='pl-5'>{message}</li>
                ))}
              </ul>
            </div>
          </Tile>

          <Tile className='p-4' style={{ display: 'flex', flexDirection: 'column', justifyContent: 'flex-end', height: '100%' }}>
            <h2>Chat</h2>
            <div style={{ flex: '1 1 auto', overflowY: 'auto', display: 'flex', flexDirection: 'column', justifyContent: 'flex-end' }}>
              <ul className='overflow-y-auto pb-4'>
                {allBroadcastMessages.map(({ id, message }) => (
                  <li key={id} className='pl-5'>
                    <span className='font-bold'>Client {id}:</span> {message}
                  </li>
                ))}
              </ul>
              <div className='flex'>
                <TextInput
                  type="text"
                  labelText="Send a message"
                  placeholder="Type your message here"
                  style={{ width: '100%' }}
                  id="text-input-1"
                />
                <div>
                  <br />
                  <Button
                    kind='ghost'
                    renderIcon={Send}
                  >
                    Send
                  </Button>
                </div>
              </div>
            </div>
          </Tile>
        </div>
      </div>
    </Layout>
  );
}

export default Game;
