import { Layout } from "../components";

function About() {
  return (
    <Layout>
      <div className='space-y-4'>
        <h1>About the Zappy</h1>
        <p>
          This app is a GUI for the Zappy server. It is a simple app that allows you to connect to a Zappy server and interact with it.
          <br />
          The app is built using React, Tailwind CSS, and Carbon Design System.
        </p>

        <h2>Features</h2>
        <ul>
          <li>- Connect to a Zappy server</li>
          <li>- Send commands to the server</li>
          <li>- View the server's responses</li>
        </ul>

        <h2>How to use</h2>
        <p>
          You'll first need to go launch the Zappy server with the port of your choice.
          <br />
          Then, you'll need to launch the server found in this repository. And pass as parameters the host and port of the Zappy server.
          <br />
          Now, you can put the host and port of the web socket server in the input fields and click on the "Connect to server" button.
          <br />
          You can now send commands to the server and view the responses.
        </p>

        <h2>About Us</h2>
        <p>
          We are a group of students from EPITECH Rennes. We are currently in our second year of the computer science program.
          <br />
          Come star our repository if you like it ;)
        </p>
      </div>
    </Layout>
  );
}

export default About;
