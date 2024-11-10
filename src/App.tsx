import { useState } from 'react'
import './App.css'
import Drop from './components/Drop'
import Playground from './components/Playground'

function App() {

  const [file, setFile] = useState<File | null>(null);

  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    console.log(e)
  };

  return (
    <div>
      <Drop />
    </div>
  )
}

export default App
