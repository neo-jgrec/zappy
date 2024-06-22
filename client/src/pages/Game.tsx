import { useRef, useState, useEffect } from 'react';
import { Layout } from "../components";
import { useWebSocket } from '../context';
import { Button, TextInput, Tile } from '@carbon/react';
import { Send } from '@carbon/icons-react';
import {
  Orientation,
  colors
} from '../utils';

function Game() {
  const canvasRef = useRef<HTMLCanvasElement | null>(null);
  const wrapperRef = useRef<HTMLDivElement | null>(null);
  const [zoom, setZoom] = useState(1);
  const [pan, setPan] = useState({ x: 0, y: 0 });
  const [isPanning, setIsPanning] = useState(false);
  const [startPan, setStartPan] = useState({ x: 0, y: 0 });
  const [mouseTile, setMouseTile] = useState({ x: 0, y: 0 });

  const { zappyServerData, hundredLastMessages, allBroadcastMessages } = useWebSocket();

  useEffect(() => {
    const canvas = canvasRef.current;
    const context = canvas?.getContext('2d');

    if (!context || !canvas) {
      console.error('Failed to get canvas context');
      return;
    }

    const tileSize = 50;

    const draw = () => {
      context.clearRect(0, 0, canvas.width, canvas.height);
      context.save();
      context.scale(zoom, zoom);
      context.translate(pan.x / zoom, pan.y / zoom);

      for (let i = 0; i < zappyServerData.x; i++) {
        for (let j = 0; j < zappyServerData.y; j++) {
          context.fillStyle = '#008000';
          context.fillRect(i * tileSize, j * tileSize, tileSize, tileSize);
          context.strokeStyle = '#000000';
          context.strokeRect(i * tileSize, j * tileSize, tileSize, tileSize);
        }
      }
      zappyServerData.player_positions.forEach(player => {
        let playerColor;
        if (player.team_name)
          playerColor = colors[zappyServerData.team_names.indexOf(player?.team_name || '')];
        else
          playerColor = '#000000';
        context.beginPath();
        context.arc(player.x * tileSize + tileSize / 2, player.y * tileSize + tileSize / 2, tileSize / 4, 0, 2 * Math.PI);
        context.fillStyle = playerColor;
        context.fill();
        context.closePath();

        if (player.orientation) {
          const arrowSize = tileSize / 2;
          const arrowX = player.x * tileSize + tileSize / 2;
          const arrowY = player.y * tileSize + tileSize / 2;
          const arrowOrientation = player.orientation;
          let rotation = 0;
          switch (arrowOrientation) {
            case Orientation.NORTH:
              rotation = 0;
              break;
            case Orientation.EAST:
              rotation = Math.PI / 2;
              break;
            case Orientation.SOUTH:
              rotation = Math.PI;
              break;
            case Orientation.WEST:
              rotation = (3 * Math.PI) / 2;
              break;
          }
          context.save();
          context.translate(arrowX, arrowY);
          context.rotate(rotation);
          context.beginPath();
          context.moveTo(0, -arrowSize / 2);
          context.lineTo(arrowSize / 2, arrowSize / 2);
          context.lineTo(-arrowSize / 2, arrowSize / 2);
          context.closePath();
          context.fillStyle = '#000000';
          context.fill();
          context.restore();
        }

        context.fillStyle = 'white';
        context.font = '25px';
        context.textAlign = 'center';
        context.fillText(player.level?.toString() || '1', player.x * tileSize + tileSize / 2, player.y * tileSize + tileSize / 2 + 4);
      });

      context.restore();
    };

    const handleResize = () => {
      if (wrapperRef.current && canvas) {
        const { width, height } = wrapperRef.current.getBoundingClientRect();
        canvas.width = width;
        canvas.height = height;
        draw();
      }
    };

    const handleWheel = (event: WheelEvent) => {
      event.preventDefault();
      const scaleAmount = -event.deltaY * 0.01;
      setZoom((prevZoom) => Math.min(Math.max(prevZoom + scaleAmount, 0.5), 3));
    };

    window.addEventListener('resize', handleResize);
    wrapperRef.current?.addEventListener('wheel', handleWheel, { passive: false });
    handleResize();

    return () => {
      window.removeEventListener('resize', handleResize);
      wrapperRef.current?.removeEventListener('wheel', handleWheel);
    };
  }, [zoom, pan, zappyServerData]);

  const handleMouseDown = (event: React.MouseEvent) => {
    setIsPanning(true);
    setStartPan({ x: event.clientX - pan.x, y: event.clientY - pan.y });
  };

  const handleMouseMove = (event: React.MouseEvent) => {
    if (isPanning) {
      setPan({ x: event.clientX - startPan.x, y: event.clientY - startPan.y });
    } else {
      const rect = wrapperRef.current?.getBoundingClientRect();
      if (rect) {
        const x = Math.floor((event.clientX - rect.left - pan.x) / (50 * zoom));
        const y = Math.floor((event.clientY - rect.top - pan.y) / (50 * zoom));
        if (x >= 0 && y >= 0) {
          setMouseTile({ x, y });
        }
      }
    }
  };

  const handleMouseUp = () => {
    setIsPanning(false);
  };

  const alertUser = (e: BeforeUnloadEvent) => {
    e.preventDefault();
    e.returnValue = "";
  };

  useEffect(() => {
    window.addEventListener("beforeunload", alertUser);
    return () => {
      window.removeEventListener("beforeunload", alertUser);
    };
  }, []);

  return (
    <Layout>
      <div className='flex space-x-4'>
        <Tile className='w-full relative h-[85vh] overflow-hidden bg-blue-900 bg-opacity-5 rounded-xl'>
          <div
            ref={wrapperRef}
            onMouseDown={handleMouseDown}
            onMouseMove={handleMouseMove}
            onMouseUp={handleMouseUp}
            onMouseLeave={handleMouseUp}
            className='w-full h-full relative'
          >
            <canvas
              ref={canvasRef}
              className='absolute top-0 left-0'
            ></canvas>
            <p className='absolute top-0 left-0 bg-white p-2 m-2 rounded shadow bg-opacity-50 text-black'>
              Tile Coordinates: ({mouseTile.x}, {mouseTile.y})
            </p>
          </div>
        </Tile>

        <div className='grid grid-cols-2 gap-4 w-full'>
          <Tile className='p-4' style={{ display: 'flex', flexDirection: 'column', justifyContent: 'flex-end', height: '100%', maxHeight: '85vh' }}>
            <h2>Game Events</h2>
            <div style={{ flex: '1 1 auto', overflowY: 'auto', display: 'flex', flexDirection: 'column', justifyContent: 'flex-end' }}>
              <ul className='overflow-y-auto'>
                {hundredLastMessages.map((message, index) => (
                  <li key={index} className='pl-5'>{message}</li>
                ))}
              </ul>
            </div>
          </Tile>

          <Tile className='p-4' style={{ display: 'flex', flexDirection: 'column', justifyContent: 'flex-end', height: '100%', maxHeight: '85vh' }}>
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
