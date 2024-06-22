import { useEffect } from "react";
import { Layout } from "../components";
import {
  DataTable
} from '@carbon/react';

function Gamble() {
  const alertUser = (e: { preventDefault: () => void; returnValue: string; }) => {
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
      <div className='flex flex-col justify-center items-center h-64'>
        <h1>Gambling</h1>
        <p>Gambling page</p>
      </div>
    </Layout>
  );
}

export default Gamble;
