import { useState } from 'react';

function Drop() {
  const [test, setTest] = useState<boolean>(false);
  return <div>Drop an elf file here!</div>
}

export default Drop;
