import { createContext, useContext, useState, useEffect, ReactNode } from 'react';
import { InlineNotification } from '@carbon/react';
import './snackbar.css';

type SnackbarContextType = {
  showSnackbar: (options?: SnackbarOptions) => void;
  hideSnackbar: () => void;
};

type SnackbarOptions = {
  title?: string;
  subtitle?: string;
  kind?: 'error' | 'info' | 'success' | 'warning';
  timeout?: number;
};

const SnackbarContext = createContext<SnackbarContextType | undefined>(undefined);

export const useSnackbar = () => {
  const context = useContext(SnackbarContext);
  if (!context) {
    throw new Error('useSnackbar must be used within a SnackbarProvider');
  }
  return context;
};

export const SnackbarProvider = ({ children }: { children: ReactNode }) => {
  const [snackbarOpen, setSnackbarOpen] = useState(false);
  const [snackbarOptions, setSnackbarOptions] = useState<SnackbarOptions>({});
  const [timeoutId, setTimeoutId] = useState<NodeJS.Timeout | null>(null);
  const [animationClass, setAnimationClass] = useState('snackbar-enter');

  const showSnackbar = (options: SnackbarOptions = {}) => {
    if (timeoutId) {
      clearTimeout(timeoutId);
    }
    setSnackbarOptions(options);
    setSnackbarOpen(true);
    setAnimationClass('snackbar-enter');
    if (options.timeout) {
      const id = setTimeout(() => {
        setAnimationClass('snackbar-exit');
        setTimeout(() => {
          setSnackbarOpen(false);
        }, 300);
      }, options.timeout);
      setTimeoutId(id);
    }
  };

  const hideSnackbar = () => {
    if (timeoutId) {
      clearTimeout(timeoutId);
    }
    setAnimationClass('snackbar-exit');
    setTimeout(() => {
      setSnackbarOpen(false);
    }, 300);
  };

  useEffect(() => {
    return () => {
      if (timeoutId) {
        clearTimeout(timeoutId);
      }
    };
  }, [timeoutId]);

  return (
    <SnackbarContext.Provider value={{ showSnackbar, hideSnackbar }}>
      {children}
      {snackbarOpen && (
        <InlineNotification
          className={animationClass}
          style={{
            zIndex: 1000,
            position: 'fixed',
            bottom: '1rem',
            right: '1rem'
          }}
          onClose={hideSnackbar}
          {...snackbarOptions}
        />
      )}
    </SnackbarContext.Provider>
  );
};
