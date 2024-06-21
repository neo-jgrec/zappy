import { useEffect } from "react";
import { useNavigate, Outlet } from "react-router-dom";
import { useWebSocket } from "../context";

function PrivateRoute() {
  const navigate = useNavigate();
  const host = useWebSocket().host;
  const port = useWebSocket().port;

  useEffect(() => {
    const validateConnection = async () => {
        if (!port || !host) {
            navigate("/prompt");
            return;
        }
    };

    validateConnection();
  }, [navigate]);

  return <Outlet />;
}

export default PrivateRoute;
