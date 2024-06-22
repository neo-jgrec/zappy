import { useMemo } from "react";
import { LineChart, ScaleTypes } from "@carbon/charts-react";
import { Layout } from "../components";
import { useWebSocket } from "../context";
import "@carbon/charts/styles.css";

function Gamble() {
  const { teamScoresState } = useWebSocket();

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
  };

  return (
    <Layout>
      <h1>Gambling</h1>
      <LineChart data={transformData} options={options} />
    </Layout>
  );
}

export default Gamble;
