import { Routes, Route } from "react-router-dom";
import { PromptServer } from "../pages";
import { WebSocketProvider, SnackbarProvider } from "../context";
import PrivateRoute from "./PrivateRoute";

function Router() {
  return (
    <SnackbarProvider>
      <WebSocketProvider>
        <Routes>
          <Route path="/prompt" element={<PromptServer />} />
          <Route path="/" element={<PrivateRoute />}>
            {/* <Route index element={<Game />} /> */}
          </Route>
          <Route path="*" element={<h1>Not Found</h1>} />
        </Routes>
      </WebSocketProvider>
    </SnackbarProvider>
  );
}

export default Router;
