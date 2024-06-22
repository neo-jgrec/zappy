import { Routes, Route, Outlet } from "react-router-dom";
import { PromptServer, NotFound, Game, Gamble, About } from "../pages";
import { WebSocketProvider, SnackbarProvider, ThemeProvider } from "../context";

function Router() {
  return (
    <SnackbarProvider>
      <ThemeProvider>
        <Routes>
          <Route path="/prompt" element={<PromptServer />} />
          <Route path="/about" element={<About />} />
          <Route path="/" element={<WebSocketProvider><Outlet/></WebSocketProvider>} >
            <Route index element={<Game />} />
            <Route path="/gamble" element={<Gamble />} />
          </Route>
          <Route path="*" element={<NotFound />} />
        </Routes>
      </ThemeProvider>
    </SnackbarProvider>
  );
}

export default Router;
