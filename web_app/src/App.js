import React, { useState, useEffect } from 'react';
import { Connection, PublicKey } from '@solana/web3.js';

const connection = new Connection('https://api.devnet.solana.com');
const programId = new PublicKey('YOUR_PROGRAM_ID');

function App() {
  const [ecgData, setEcgData] = useState([]);

  useEffect(() => {
    const fetchEcgData = async () => {
      // Fetch data from Solana blockchain
      // You need to implement the logic to fetch and deserialize the data
      const data = await fetchEcgDataFromSolana();
      setEcgData(data);
    };

    fetchEcgData();
  }, []);

  const fetchEcgDataFromSolana = async () => {
    // Implement the logic to fetch ECG data from the Solana program
    // This is a placeholder for your actual implementation
    return [];
  };

  return (
    <div className="App">
      <h1>ECG Data</h1>
      <ul>
        {ecgData.map((data, index) => (
          <li key={index}>{data}</li>
        ))}
      </ul>
    </div>
  );
}

export default App;
