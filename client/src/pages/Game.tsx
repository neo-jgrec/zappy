import { useRef, useState, useEffect } from 'react';
import { Layout } from "../components";
import { useWebSocket } from '../context';

function Game() {
  const canvasRef = useRef(null);
  const [zoom, setZoom] = useState(1);
  const [pan, setPan] = useState({ x: 0, y: 0 });
  const [isPanning, setIsPanning] = useState(false);
  const [startPan, setStartPan] = useState({ x: 0, y: 0 });

  const { hundredLastMessages } = useWebSocket();

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
      <div className='grid grid-cols-2 gap-4'>
        <div className='w-full'>
          <div
            className='relative w-[85vh] h-[85vh] bg-gray-800 overflow-hidden'
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
        </div>
        <div className='w-1/2 grid grid-cols-2 gap-4'>
          <div className='w-full'>
            It is real chat?
          </div>
          <div className='w-full h-[58vh] overflow-y-auto'>
            <ul>
              {hundredLastMessages.map((message, index) => (
                <li key={index}>{message}</li>
              ))}
            </ul>
          </div>
        </div>
      </div>
    </Layout>
  );
}

export default Game;
