import {
  Header,
  HeaderGlobalAction,
  HeaderGlobalBar,
  HeaderMenuItem,
  HeaderName,
  HeaderNavigation,
} from '@carbon/react';
import {
  Moon,
  Sun,
  LogoGithub
} from '@carbon/icons-react';

type Theme = 'g100' | 'white' | 'g10' | 'g90';

interface HeaderComponentProps {
  theme: string;
  setTheme: (theme: Theme) => void;
}

function HeaderComponent({ theme, setTheme }: HeaderComponentProps) {
  return (
    <Header aria-label='Zappy'>
      <HeaderName href='/' prefix='Zappy / '>
        A tribute to Zaphod Beeblebrox
      </HeaderName>
      <HeaderNavigation aria-label='Zappy'>
        <HeaderMenuItem href='/' isActive={window.location.pathname === '/'}>
          Game
        </HeaderMenuItem>
        <HeaderMenuItem href='/gamble' isActive={window.location.pathname === '/gamble'}>
          Gamble
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
  );
}

export default HeaderComponent;
