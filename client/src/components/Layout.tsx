import { ReactNode, useState } from 'react';
import PropTypes from 'prop-types';
import { useEffect } from 'react';
import {
  GlobalTheme,
  Header,
  HeaderGlobalAction,
  HeaderGlobalBar,
  HeaderMenuItem,
  HeaderName,
  HeaderNavigation,
  Theme,
} from '@carbon/react';
import {
  Moon,
  Sun,
  LogoGithub
} from '@carbon/icons-react';

interface LayoutProps {
  children: ReactNode;
}

type Theme = 'g100' | 'white' | 'g10' | 'g90';

const Layout = ({ children }: LayoutProps) => {
  Layout.propTypes = {
    children: PropTypes.node
  };

  const [theme, setTheme] = useState<Theme>(localStorage.getItem('theme') as Theme || 'g100');

  useEffect(() => {
    document.documentElement.dataset.carbonTheme = theme;
    localStorage.setItem('theme', theme);
  }, [theme]);

  return (
    <GlobalTheme theme={theme}>
      <Theme theme={theme}>
        <div className='flex flex-col min-h-screen'>
          <Header aria-label='Zappy'>
            <HeaderName href='/' prefix='Zappy / '>
              A tribute to Zaphod Beeblebrox
            </HeaderName>
            <HeaderNavigation aria-label='Zappy'>
              <HeaderMenuItem href='/' isActive={window.location.pathname === '/'}>
                Game
              </HeaderMenuItem>
              <HeaderMenuItem href='/prompt' isActive={window.location.pathname === '/prompt'}>
                Change Server
              </HeaderMenuItem>
              <HeaderMenuItem href='/about' isActive={window.location.pathname === '/about'}>
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
          <div className='flex flex-col flex-1 px-5 lg:px-36 py-10 z-[2] pt-20'>
            {children}
          </div>
        </div>
      </Theme>
    </GlobalTheme>
  );
};

Layout.propTypes = {
  children: PropTypes.node
};

export default Layout;
