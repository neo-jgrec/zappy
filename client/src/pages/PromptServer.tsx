import { useWebSocket } from '../context/WebSocketContext';
import { Button, TextInput } from '@carbon/react';
import { Layout } from '../components';
import {
  ArrowRight
} from '@carbon/icons-react';
import { useNavigate } from 'react-router-dom';

const PromptServer = () => {
  const { host = '', port = '', setPort, setHost } = useWebSocket();
  const navigate = useNavigate();

  return (
    <Layout>
      <div className='flex flex-col space-y-5 items-center'>
        <h1 className='pb-5'>
          Enter the server details
          <br />
          <p className='text-sm'>
            (The WebSocket one)
          </p>
        </h1>
        <TextInput
          id='host'
          labelText='Host'
          placeholder='127.0.0.1'
          style={{ maxWidth: '500px', width: '500px' }}
          value={host}
          onChange={(e) => setHost(e.target.value)}
        />
        <TextInput
          id='port'
          labelText='Port'
          placeholder='8080'
          style={{ maxWidth: '500px', width: '500px' }}
          value={port}
          onChange={(e) => setPort(e.target.value)}
        />
        <Button
          className='w-40'
          style={{ maxWidth: '500px', width: '500px' }}
          renderIcon={ArrowRight}
          onClick={() => {
            navigate('/');
          }}
        >
          Connect to server
        </Button>
      </div>
    </Layout>
  );
};

export default PromptServer;
