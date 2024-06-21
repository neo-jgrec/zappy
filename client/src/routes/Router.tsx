import { Routes, Route } from "react-router-dom";
import { PromptServer, NotFound, Game, Gamble } from "../pages";
import { WebSocketProvider, SnackbarProvider } from "../context";
import PrivateRoute from "./PrivateRoute";

function Router() {
  return (
    <SnackbarProvider>
      <WebSocketProvider>
        <Routes>
          <Route path="/prompt" element={<PromptServer />} />
          <Route path="/" element={<PrivateRoute />}>
            <Route index element={<Game />} />
            <Route path="/gamble" element={<Gamble />} />
          </Route>
          <Route path="*" element={<NotFound />} />
        </Routes>
      </WebSocketProvider>
    </SnackbarProvider>
  );
}

export default Router;
