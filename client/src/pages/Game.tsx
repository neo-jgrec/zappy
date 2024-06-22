import { useRef, useState, useEffect } from 'react';
import { Layout } from "../components";
import { useWebSocket } from '../context';
import { Send } from '@carbon/icons-react';
import {
  Orientation,
  colors
} from '../utils';
import {
  DataTable,
  Table,
  TableHead,
  TableRow,
  TableHeader,
  TableBody,
  TableCell,
  Button,
  TextInput,
  Tile,
  TableContainer,
  TableToolbar,
  TableToolbarContent,
  TableToolbarSearch,
  TableToolbarMenu,
  TableToolbarAction
} from '@carbon/react';
import {
  white,
} from '@carbon/colors';

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
      zappyServerData.players.forEach(player => {
        if (player.is_dead) return;
        let playerColor;
        if (player.team_name)
          playerColor = colors[zappyServerData.teams.indexOf(player?.team_name || '')];
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

  return (
    <Layout>
      <h1 className='pb-2'>Game</h1>
      <div className='flex space-x-4'>
        <Tile className='w-full relative h-[85vh] overflow-hidden'>
          <h2>
            Map
          </h2>
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
                {hundredLastMessages.map((node, index) => (
                  <li key={index} className='pl-5'>
                    {node.message}
                  </li>
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

      <h1 className='pt-4'>Additionnal Data</h1>
      <DataTable
          isSortable={true}
          headers={[
            {
              key: 'id',
              header: 'ID'
            },
            {
              key: 'team_name',
              header: 'Team'
            },
            {
              key: 'x',
              header: 'X'
            },
            {
              key: 'y',
              header: 'Y'
            },
            {
              key: 'orientation',
              header: 'Orientation'
            },
            {
              key: 'level',
              header: 'Level'
            },
            {
              key: 'food',
              header: 'Food'
            },
            {
              key: 'linemate',
              header: 'Linemate'
            },
            {
              key: 'deraumere',
              header: 'Deraumere'
            },
            {
              key: 'sibur',
              header: 'Sibur'
            },
            {
              key: 'mendiane',
              header: 'Mendiane'
            },
            {
              key: 'phiras',
              header: 'Phiras'
            },
            {
              key: 'thystame',
              header: 'Thystame'
            },
            {
              key: 'is_dead',
              header: 'Status'
            }
          ]}
          rows={zappyServerData.players.map((player) => ({
            id: player.id.toString(),
            team_name: player.team_name,
            x: player.x.toString(),
            y: player.y.toString(),
            orientation: player.orientation?.toString(),
            level: player.level?.toString(),
            food: player.resources?.food?.toString() || '0',
            linemate: player.resources?.linemate?.toString() || '0',
            deraumere: player.resources?.deraumere?.toString() || '0',
            sibur: player.resources?.sibur?.toString() || '0',
            mendiane: player.resources?.mendiane?.toString() || '0',
            phiras: player.resources?.phiras?.toString() || '0',
            thystame: player.resources?.thystame?.toString() || '0',
            is_dead: player.is_dead ? 'Dead' : 'Alive'
          }))}
        >
          {({
            rows,
            headers,
            getHeaderProps,
            getRowProps,
            getTableProps,
            onInputChange,
          }) => (
            <TableContainer title="Players" description="List of players with their data" className='mt-4'>
              <TableToolbar>
                <TableToolbarContent>
                  <TableToolbarSearch onChange={() => {}} />
                  <TableToolbarMenu>
                    <TableToolbarAction onClick={() => {} }>
                      Action 1
                    </TableToolbarAction>
                    <TableToolbarAction onClick={() => {} }>
                      Action 2
                    </TableToolbarAction>
                    <TableToolbarAction onClick={() => {} }>
                      Action 3
                    </TableToolbarAction>
                  </TableToolbarMenu>
                  <Button onClick={() => {} }>Primary Button</Button>
                </TableToolbarContent>
              </TableToolbar>
              <Table {...getTableProps()}>
                <TableHead>
                  <TableRow>
                    {headers.map((header) => (
                      <TableHeader {...getHeaderProps({ header })}>
                        {header.header}
                      </TableHeader>
                    ))}
                  </TableRow>
                </TableHead>
                <TableBody>
                  {rows.map((row) => (
                    <TableRow {...getRowProps({ row })} style={{ backgroundColor: row.cells[13].value === 'Dead' ? '#A34343' : '' }}>
                      {row.cells.map((cell) => (
                        <TableCell style={{ color: row.cells[13].value === 'Dead' ? `${white}` : '' }}>
                          {cell.value}
                        </TableCell>
                      ))}
                    </TableRow>
                  ))}
                </TableBody>
              </Table>
            </TableContainer>
          )}
        </DataTable>
    </Layout>
  );
}

export default Game;
