import { useEffect, useState } from "react";
import { useNavigate, Outlet } from "react-router-dom";
import { useSnackbar, useWebSocket } from "../context";
import { Layout } from "../components";
import { Loading } from "@carbon/react";

function PrivateRoute() {
    const navigate = useNavigate();
    const { showSnackbar } = useSnackbar();
    const { host, port, connect, connectionStatus } = useWebSocket();

    const [isLoaded, setIsLoaded] = useState(false);

    useEffect(() => {
        const validateConnection = async () => {
            if (!port || !host) {
                showSnackbar({
                    title: "Info",
                    subtitle: "Host and Port are required to connect",
                    kind: "info",
                    timeout: 5000
                });
                navigate("/prompt");
                return;
            }

            if (connectionStatus === 'disconnected') {
                connect(host, port);
            }

            const checkConnection = setInterval(() => {
                if (connectionStatus === 'connected') {
                    setIsLoaded(true);
                    clearInterval(checkConnection);
                } else if (connectionStatus === 'error') {
                    clearInterval(checkConnection);
                }
            }, 100);

        };

        validateConnection();
    }, [navigate, host, port, connectionStatus]);

    if (!isLoaded) {
        return (
          <Layout>
            <div className="flex flex-col justify-center items-center h-64">
              <Loading description="Loading..." withOverlay={false} />
            </div>
          </Layout>
        )
    }

    return <Outlet />;
}

export default PrivateRoute;
