const boardEl = document.getElementById('board');
const logEl = document.getElementById('log');
const playControls = document.getElementById('play-controls');
let grid = Array.from({length:9},()=>Array(9).fill(0));
let steps = [];
let stepIndex = 0;
let playing = false;
let intervalId = null;

function buildBoard(){
  boardEl.innerHTML = '';
  for(let r=0;r<9;r++){
    for(let c=0;c<9;c++){
      const div = document.createElement('div');
      div.className = 'cell';
      div.dataset.r=r; div.dataset.c=c;
      if((c+1)%3===0 && c!==8) div.classList.add('box-border');
      if((r+1)%3===0 && r!==8) div.classList.add('row-border-bottom');
      const input = document.createElement('input');
      input.type='text'; input.maxLength=1;
      input.value = grid[r][c]===0?'':grid[r][c];
      input.addEventListener('input', (e)=>{
        let v = e.target.value.replace(/[^1-9]/g,'');
        e.target.value = v;
        grid[r][c] = v?parseInt(v):0;
      });
      div.appendChild(input);
      boardEl.appendChild(div);
    }
  }
}

function setCell(r,c,v,cssClass=null){
  const idx = r*9 + c;
  const div = boardEl.children[idx];
  const input = div.querySelector('input');
  input.value = v===0?'':v;
  div.classList.remove('highlight','backtrack');
  if(cssClass) div.classList.add(cssClass);
}

function log(msg){
  logEl.textContent += msg + "\n";
  logEl.scrollTop = logEl.scrollHeight;
}

document.getElementById('btn-clear').addEventListener('click', ()=>{
  grid = Array.from({length:9},()=>Array(9).fill(0));
  buildBoard();
  log("Cleared.");
});

document.getElementById('btn-random').addEventListener('click', ()=>{
  const samples = [
    [5,3,0,0,7,0,0,0,0, 6,0,0,1,9,5,0,0,0, 0,9,8,0,0,0,0,6,0, 
     8,0,0,0,6,0,0,0,3, 4,0,0,8,0,3,0,0,1, 7,0,0,0,2,0,0,0,6,
     0,6,0,0,0,0,2,8,0, 0,0,0,4,1,9,0,0,5, 0,0,0,0,8,0,0,7,9],
  ];
  const arr = samples[Math.floor(Math.random()*samples.length)];
  grid = [];
  for(let r=0;r<9;r++) grid.push(arr.slice(r*9, r*9+9));
  buildBoard();
  log("Loaded sample puzzle.");
});

document.getElementById('btn-solve').addEventListener('click', async ()=>{
  for(let r=0;r<9;r++){
    for(let c=0;c<9;c++){
      const v = boardEl.children[r*9+c].querySelector('input').value;
      grid[r][c] = v?parseInt(v):0;
    }
  }
  const algo = document.getElementById('algo').value;
  const payload = {grid};
  if(algo==='csp'){
    log("Sending to CSP solver...");
    const resp = await fetch('/solve_csp', {
      method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(payload)
    });
    const data = await resp.json();
    handleResult(data);
  } else {
    log("Sending to Min-Conflicts solver...");
    const resp = await fetch('/solve_minconflict', {
      method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(payload)
    });
    const data = await resp.json();
    handleResult(data);
  }
});

function handleResult(data){
  console.log(data);
  if(!data.steps || data.steps.length===0){
    if(data.solution){
      for(let r=0;r<9;r++) for(let c=0;c<9;c++) setCell(r,c,data.solution[r][c]);
      log("Solution applied. success="+data.success);
      if(data.success===false){
        log(`Note: solver reported failure. final_cost=${data.final_cost} ${data.message||''}`);
      }
    }
    return;
  }
  steps = data.steps;
  stepIndex = 0;
  playControls.style.display = 'block';
  document.getElementById('status').textContent = `0 / ${steps.length} steps`;
  logEl.textContent = "";
  for(let r=0;r<9;r++) for(let c=0;c<9;c++) setCell(r,c, grid[r][c]);
  log(`Received ${steps.length} steps. Use Play/Step to animate.`);
  if(document.getElementById('step-toggle').checked) {
  } else {
    if(data.solution){
      for(let r=0;r<9;r++) for(let c=0;c<9;c++) setCell(r,c,data.solution[r][c]);
      if(data.success===false){
        log(`Min-Conflicts did not reach full solution. final_cost=${data.final_cost} ${data.message||''}`);
      }
    }
  }
}

document.getElementById('btn-play').addEventListener('click', ()=>{
  if(playing) return;
  playing = true;
  const delay = parseInt(document.getElementById('delay').value) || 200;
  intervalId = setInterval(()=>{ doStep(); }, delay);
});

document.getElementById('btn-pause').addEventListener('click', ()=>{
  playing = false;
  if(intervalId) clearInterval(intervalId);
});

document.getElementById('btn-step').addEventListener('click', ()=>{ doStep(); });

function doStep(){
  if(stepIndex >= steps.length){
    playing = false;
    if(intervalId) clearInterval(intervalId);
    log("Animation finished.");
    return;
  }
  const s = steps[stepIndex++];
  if(s.type==='set' || s.type==='set_init'){
    setCell(s.r, s.c, s.v, 'highlight');
    log(`Set [${s.r},${s.c}] = ${s.v}`);
  } else if(s.type==='backtrack'){
    setCell(s.r, s.c, 0, 'backtrack');
    log(`Backtrack [${s.r},${s.c}] cleared`);
  } else if(s.type==='choose_swap'){
    log(`Choose swap at row ${s.r}, col ${s.c} with ${s.swap_with} (${s.reason}) -> cost ${s.new_cost||''}`);
  } else if(s.type==='swap'){
    const r = s.r, c = s.c, swapc = s.with_c;
    const valA = boardEl.children[r*9+c].querySelector('input').value || '';
    const valB = boardEl.children[r*9+swapc].querySelector('input').value || '';
    boardEl.children[r*9+c].querySelector('input').value = valB;
    boardEl.children[r*9+swapc].querySelector('input').value = valA;
    const divA = boardEl.children[r*9+c];
    const divB = boardEl.children[r*9+swapc];
    if(!divA.classList.contains('backtrack')) divA.classList.remove('highlight');
    if(!divB.classList.contains('backtrack')) divB.classList.remove('highlight');
    divA.classList.add('highlight');
    divB.classList.add('highlight');
    log(`Swap row ${r} cols ${c} <-> ${swapc} -> cost ${s.cost}`);
  }
  document.getElementById('status').textContent = `${stepIndex} / ${steps.length} steps`;
}
buildBoard();
