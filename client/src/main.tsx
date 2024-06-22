import ReactDOM from 'react-dom/client';
import { BrowserRouter } from 'react-router-dom';
import { Router } from './routes';
import './index.css';
import '@carbon/react/index.scss';
import '@carbon/themes/scss/_theme.scss';
import '@carbon/charts-react/styles.css'

ReactDOM.createRoot(document.getElementById('root')!).render(
    <BrowserRouter>
      <Router />
    </BrowserRouter>
);
