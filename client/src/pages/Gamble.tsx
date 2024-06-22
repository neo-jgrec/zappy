import { useMemo, useState } from "react";
import { DonutChart, LineChart, ScaleTypes } from "@carbon/charts-react";
import { Layout } from "../components";
import { useTheme, useWebSocket } from "../context";
import QRCode from 'qrcode.react';
import '@carbon/charts/styles.css'
import { Button, Modal } from "@carbon/react";
import {
  QrCode
} from '@carbon/icons-react';

function Gamble() {
  const { teamScoresState } = useWebSocket();
  const { theme } = useTheme();
  const [isModalOpen, setIsModalOpen] = useState(false);

  const transformData = useMemo(() => {
    const data: { group: string; date: Date; value: any; }[] = [];
    Object.keys(teamScoresState).forEach((team) => {
      teamScoresState[team].scores.forEach((score) => {
        data.push({
          group: team,
          date: new Date(score.timestamp),
          value: score.value,
        });
      });
    });
    return data;
  }, [teamScoresState]);

  const options = {
    title: "Team Scores",
    axes: {
      bottom: {
        title: 'Timestamp',
        mapsTo: 'date',
        scaleType: ScaleTypes.TIME
      },
      left: {
        mapsTo: 'value',
        title: 'Score',
        scaleType: ScaleTypes.LINEAR
      }
    },
    height: "400px",
    curve: 'curveMonotoneX',
    theme,
  };

  const transformToDonutData = useMemo(() => {
    const data: { group: string; value: number; }[] = [];
    Object.keys(teamScoresState).forEach((team) => {
      const total = teamScoresState[team].scores.reduce((acc, score) => acc + score.value, 0);
      data.push({ group: team, value: total });
    });
    return data;
  }, [teamScoresState]);

  const donnutOptions = {
    title: "Points Distribution",
    data: {
      groupMapsTo: 'group',
      valueMapsTo: 'value',
    },
    donut: {
      center: {
        label: 'All Gained Points',
      },
    },
    height: "400px",
    theme,
  };

  return (
    <Layout>
      <div className='flex justify-between mb-10'>
        <h1>Gambling</h1>
        <Button
          onClick={() => setIsModalOpen(true)}
          renderIcon={QrCode}
        >
          Scan to join
        </Button>
      </div>
      <div className='w-full h-[400px] flex items-center justify-center flex-row'>
        <div className='w-2/3 h-full'>
          <LineChart
            data={transformData}
            options={options}
          />
        </div>
        <div className='h-full border-r-2 border-gray-300 mx-10' />
        <div className='h-full'>
          <DonutChart
            data={transformToDonutData}
            options={donnutOptions}
          />
        </div>
      </div>
      <Modal
        open={isModalOpen}
        modalHeading='Scan to join the game'
        primaryButtonText='Close'
        onRequestClose={() => setIsModalOpen(false)}
        onRequestSubmit={() => setIsModalOpen(false)}
        onSecondarySubmit={() => setIsModalOpen(false)}
      >
        <QRCode
          className='w-1/2 mx-auto'
          size={500}
          value={window.location.href}
        />
      </Modal>
    </Layout>
  );
}

export default Gamble;
