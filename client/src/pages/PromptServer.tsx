import { Button, TextInput } from '@carbon/react';
import { Layout } from '../components';
import {
  ArrowRight
} from '@carbon/icons-react';
import { useNavigate } from 'react-router-dom';
import { useState } from 'react';

const PromptServer = () => {
  const navigate = useNavigate();

  const [host, setHost] = useState(localStorage.getItem('host') || '');
  const [port, setPort] = useState(localStorage.getItem('port') || '');
  const [tcpHost, setTcpHost] = useState(localStorage.getItem('tcpHost') || '');
  const [tcpPort, setTcpPort] = useState(localStorage.getItem('tcpPort') || '');

  return (
    <Layout>
      <div className='flex flex-col space-y-10 items-center mt-10'>
        <div className='flex flex-col space-y-5 items-center'>
          <h1 className='pb-5'>
            Enter the server details
          </h1>
          <TextInput
            id='host'
            labelText='Host'
            placeholder='127.0.0.1'
            style={{ maxWidth: '500px', width: '500px' }}
            value={host}
            onChange={(e) => {
              setHost(e.target.value);
              localStorage.setItem('host', e.target.value);
            }}
          />
          <TextInput
            id='port'
            labelText='Port'
            placeholder='8080'
            style={{ maxWidth: '500px', width: '500px' }}
            value={port}
            onChange={(e) => {
              setPort(e.target.value);
              localStorage.setItem('port', e.target.value);
            }}
          />
        </div>
        <div className='flex flex-col space-y-5 items-center pt-10'>
          <h1 className='pb-5'>
            Enter the TCP server details
          </h1>
          <TextInput
            id='tcpHost'
            labelText='Host'
            placeholder='54.25.36.2'
            style={{ maxWidth: '500px', width: '500px' }}
            value={tcpHost}
            onChange={(e) => {
              setTcpHost(e.target.value);
              localStorage.setItem('tcpHost', e.target.value);
            }}
          />
          <TextInput
            id='tcpPort'
            labelText='Port'
            placeholder='8080'
            style={{ maxWidth: '500px', width: '500px' }}
            value={tcpPort}
            onChange={(e) => {
              setTcpPort(e.target.value);
              localStorage.setItem('tcpPort', e.target.value);
            }}
          />
        </div>
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
