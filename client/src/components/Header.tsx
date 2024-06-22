import {
  Header,
  HeaderGlobalAction,
  HeaderGlobalBar,
  HeaderMenuItem,
  HeaderName,
  HeaderNavigation,
} from '@carbon/react';
import { Moon, Sun, LogoGithub } from '@carbon/icons-react';
import { useNavigate } from 'react-router-dom';
import { useTheme } from '../context/ThemeContext';

const HeaderComponent = () => {
  const navigate = useNavigate();
  const { theme, setTheme } = useTheme();

  return (
    <Header aria-label='Zappy'>
      <HeaderName href='/' prefix='Zappy / '>
        A tribute to Zaphod Beeblebrox
      </HeaderName>
      <HeaderNavigation aria-label='Zappy'>
        <HeaderMenuItem isActive={window.location.pathname === '/'} onClick={() => navigate('/')}>
          Game
        </HeaderMenuItem>
        <HeaderMenuItem isActive={window.location.pathname === '/gamble'} onClick={() => navigate('/gamble')}>
          Gamble
        </HeaderMenuItem>
        <HeaderMenuItem isActive={window.location.pathname === '/prompt'} onClick={() => navigate('/prompt')}>
          Change Server
        </HeaderMenuItem>
        <HeaderMenuItem isActive={window.location.pathname === '/about'} onClick={() => navigate('/about')}>
          About
        </HeaderMenuItem>
      </HeaderNavigation>
      <HeaderGlobalBar>
        <HeaderGlobalAction
          aria-label='Github'
          onClick={() => {
            window.open('https://github.com/neo-jgrec/zappy', '_blank');
          }}
        >
          <LogoGithub />
        </HeaderGlobalAction>
        <HeaderGlobalAction
          aria-label='Switch theme'
          tooltipAlignment='end'
          onClick={() => {
            setTheme(theme === 'g100' ? 'g10' : 'g100');
          }}
        >
          {theme === 'g100' ? <Sun /> : <Moon />}
        </HeaderGlobalAction>
      </HeaderGlobalBar>
    </Header>
  );
};

export default HeaderComponent;
