import { ReactNode, useState } from 'react';
import PropTypes from 'prop-types';
import { useEffect } from 'react';
import {
  GlobalTheme,
  Theme,
} from '@carbon/react';
import HeaderComponent from './Header';

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
          <HeaderComponent
            theme={theme}
            setTheme={setTheme}
          />
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
