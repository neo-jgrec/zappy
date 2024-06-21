import { Layout } from "../components";

function NotFound() {
    return (
        <Layout>
            <div className='flex flex-col justify-center items-center h-64'>
                <h1>Page Not Found</h1>
                <p>Sorry, the page you are looking for does not exist.</p>
            </div>
        </Layout>
    );
}

export default NotFound;
