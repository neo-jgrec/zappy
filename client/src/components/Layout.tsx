import { ReactNode } from 'react';
import { GlobalTheme, Theme } from '@carbon/react';
import HeaderComponent from './Header';
import { useTheme } from '../context/ThemeContext';

interface LayoutProps {
  children: ReactNode;
}

const Layout = ({ children }: LayoutProps) => {
  const { theme } = useTheme();

  return (
    <GlobalTheme theme={theme}>
      <Theme theme={theme}>
        <div className='flex flex-col min-h-screen'>
          <HeaderComponent />
          <div className='flex flex-col flex-1 px-5 lg:px-36 py-10 z-[2] pt-20'>
            {children}
          </div>
        </div>
      </Theme>
    </GlobalTheme>
  );
};

export default Layout;
