<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>Parallel Computing (SE3082) — Lab Activities | IT23226128</title>
  <meta name="description" content="SE3082 Parallel Computing lab activities for SLIIT by Geeth Bandara Seneviratne (IT23226128)." />
  <style>
    :root{
      --bg: #0b0c0f;
      --card: #13151a;
      --text: #e8e9ee;
      --muted: #b6bcc8;
      --brand: #7c9cff;
      --accent: #2bd1a6;
      --border: #242835;
      --code: #0f1220;
      --shadow: 0 10px 30px rgba(0,0,0,.35);
    }
    @media (prefers-color-scheme: light){
      :root{
        --bg: #f7f9fc;
        --card: #ffffff;
        --text: #111318;
        --muted: #545969;
        --brand: #3a5eff;
        --accent: #0aa57a;
        --border: #e7eaf0;
        --code: #f3f5fa;
        --shadow: 0 10px 30px rgba(16,24,40,.08);
      }
    }
    *{box-sizing:border-box}
    html,body{margin:0;padding:0;background:var(--bg);color:var(--text);font:16px/1.6 system-ui, -apple-system, Segoe UI, Roboto, Helvetica, Arial, "Apple Color Emoji", "Segoe UI Emoji"}
    a{color:var(--brand);text-decoration:none}
    a:hover{text-decoration:underline}
    .wrap{max-width:1100px;margin:0 auto;padding:32px 20px 64px}
    header{display:flex;gap:16px;align-items:center;margin-bottom:28px}
    .logo{width:44px;height:44px;border-radius:12px;background:linear-gradient(135deg,var(--brand),var(--accent));display:grid;place-items:center;color:white;font-weight:700;box-shadow:var(--shadow)}
    h1{font-size:clamp(1.4rem,2.6vw,2rem);margin:0}
    .subtitle{color:var(--muted);margin-top:2px}
    .grid{display:grid;grid-template-columns: repeat(auto-fit,minmax(280px,1fr));gap:16px;margin-top:10px}
    .card{background:var(--card);border:1px solid var(--border);border-radius:16px;padding:18px;box-shadow:var(--shadow)}
    .card h3{margin:0 0 8px 0;font-size:1.05rem}
    .meta{display:flex;flex-wrap:wrap;gap:8px;margin:10px 0 0}
    .badge{padding:6px 10px;border-radius:999px;border:1px solid var(--border);background:transparent;font-size:.9rem;color:var(--muted)}
    .list{margin:0;padding-left:18px}
    .muted{color:var(--muted)}
    .kbd{font-family:ui-monospace,SFMono-Regular,Menlo,Monaco,Consolas,"Liberation Mono","Courier New",monospace;font-size:.95rem;background:var(--code);border:1px solid var(--border);padding:2px 6px;border-radius:6px}
    pre{margin:10px 0 0;background:var(--code);border:1px solid var(--border);padding:14px;border-radius:12px;overflow:auto}
    code{font-family:ui-monospace,SFMono-Regular,Menlo,Monaco,Consolas,"Liberation Mono","Courier New",monospace}
    .row{display:flex;gap:8px;align-items:center;flex-wrap:wrap;margin-top:8px}
    button.copy{border:1px solid var(--border);background:transparent;color:var(--text);padding:6px 10px;border-radius:10px;cursor:pointer}
    button.copy:hover{border-color:var(--brand)}
    .labs .lab{border:1px dashed var(--border);border-radius:14px;padding:14px;margin-top:10px}
    footer{margin-top:32px;color:var(--muted);font-size:.95rem}
    .small{font-size:.95rem}
  </style>
</head>
<body>
  <div class="wrap">
    <header>
      <div class="logo" aria-hidden="true">PC</div>
      <div>
        <h1>Parallel Computing (SE3082) — Lab Activities</h1>
        <div class="subtitle">Sri Lanka Institute of Information Technology (SLIIT) • 3rd Year — 1st Semester</div>
      </div>
    </header>

    <section class="grid">
      <article class="card">
        <h3>📌 Module Information</h3>
        <ul class="list">
          <li><strong>Module:</strong> Parallel Computing</li>
          <li><strong>Code:</strong> SE3082</li>
          <li><strong>Focus:</strong> Parallelism &amp; Concurrency, OpenMP, MPI, Performance &amp; Optimization</li>
        </ul>
        <div class="meta">
          <span class="badge">OpenMP</span>
          <span class="badge">MPI</span>
          <span class="badge">C/C++</span>
          <span class="badge">Linux</span>
          <span class="badge">GCC</span>
        </div>
      </article>

      <article class="card">
        <h3>👨‍🎓 Student</h3>
        <ul class="list">
          <li><strong>Name:</strong> Geeth Bandara Seneviratne</li>
          <li><strong>Student ID:</strong> IT23226128</li>
          <li><strong>Institute:</strong> SLIIT</li>
          <li><strong>Repo:</strong> <span class="muted">Add your GitHub link here</span></li>
        </ul>
      </article>

      <article class="card">
        <h3>🚀 Quick Start</h3>
        <div class="small muted">Clone your repository and run labs locally.</div>
        <pre><code id="cmd-clone">git clone https://github.com/&lt;your-username&gt;/Parallel-Computing-SE3082.git
cd Parallel-Computing-SE3082</code></pre>
        <div class="row"><button class="copy" data-target="cmd-clone">Copy</button></div>

        <div class="small" style="margin-top:10px"><strong>Compile (OpenMP)</strong></div>
        <pre><code id="cmd-omp">gcc -fopenmp lab01.c -o lab01
./lab01</code></pre>
        <div class="row"><button class="copy" data-target="cmd-omp">Copy</button></div>

        <div class="small" style="margin-top:10px"><strong>Compile (MPI)</strong></div>
        <pre><code id="cmd-mpi">mpicc lab04.c -o lab04
mpirun -np 4 ./lab04</code></pre>
        <div class="row"><button class="copy" data-target="cmd-mpi">Copy</button></div>
      </article>
    </section>

    <section class="card" style="margin-top:16px">
      <h3>📂 Repository Structure</h3>
      <pre><code>📦 Parallel-Computing-SE3082
 ┣ 📂 Lab01  — Introduction to Parallel Computing
 ┃ ┣ 📜 lab01.c
 ┃ ┣ 📜 README.md
 ┣ 📂 Lab02  — OpenMP Basics
 ┃ ┣ 📜 lab02.c
 ┃ ┣ 📜 README.md
 ┣ 📂 Lab03  — Work Sharing &amp; Synchronization
 ┃ ┣ 📜 lab03.c
 ┃ ┣ 📜 README.md
 ┣ 📂 Lab04  — MPI Programming
 ┃ ┣ 📜 lab04.c
 ┃ ┣ 📜 README.md
 ┣ 📜 README.md  — This page</code></pre>
    </section>

    <section class="card labs">
      <h3>🧪 Lab Index</h3>

      <div class="lab">
        <div><strong>Lab 01:</strong> Introduction to Parallel Computing</div>
        <div class="muted small">Concepts of parallelism, speedup, Amdahl’s law, environment setup.</div>
        <pre><code>// build & run (OpenMP)
gcc -fopenmp lab01.c -o lab01
./lab01</code></pre>
      </div>

      <div class="lab">
        <div><strong>Lab 02:</strong> OpenMP Basics</div>
        <div class="muted small">Parallel regions, threads, work-sharing (for), reductions.</div>
        <pre><code>// build & run
gcc -fopenmp lab02.c -o lab02
./lab02</code></pre>
      </div>

      <div class="lab">
        <div><strong>Lab 03:</strong> Work Sharing &amp; Synchronization</div>
        <div class="muted small">critical, atomic, barrier, sections; scheduling strategies.</div>
        <pre><code>// build & run
gcc -fopenmp lab03.c -o lab03
./lab03</code></pre>
      </div>

      <div class="lab">
        <div><strong>Lab 04:</strong> MPI Programming</div>
        <div class="muted small">Point-to-point, collectives, ranks &amp; communicators.</div>
        <pre><code>// build & run
mpicc lab04.c -o lab04
mpirun -np 4 ./lab04</code></pre>
      </div>

      <!-- Duplicate this block for more labs -->
      <!--
      <div class="lab">
        <div><strong>Lab 05:</strong> Title here</div>
        <div class="muted small">Short description.</div>
        <pre><code>// commands here</code></pre>
      </div>
      -->
    </section>

    <section class="grid" style="margin-top:16px">
      <article class="card">
        <h3>🧰 Tooling</h3>
        <ul class="list">
          <li><strong>Compiler:</strong> GCC</li>
          <li><strong>Runtimes:</strong> OpenMP, OpenMPI</li>
          <li><strong>OS:</strong> Linux (recommended)</li>
          <li><strong>VCS:</strong> Git &amp; GitHub</li>
        </ul>
      </article>
      <article class="card">
        <h3>📜 License & Usage</h3>
        <p class="small">This repository is for educational use in <strong>SE3082 Parallel Computing</strong> at <strong>SLIIT</strong>. Feel free to reference code with attribution.</p>
      </article>
    </section>

    <footer>
      <div><strong>Maintainer:</strong> Geeth Bandara Seneviratne • <span class="muted">IT23226128</span></div>
      <div class="muted">© <span id="year"></span> SLIIT — Parallel Computing (SE3082)</div>
    </footer>
  </div>

  <script>
    // set footer year
    document.getElementById('year').textContent = new Date().getFullYear();

    // copy buttons
    document.querySelectorAll('button.copy').forEach(btn=>{
      btn.addEventListener('click', ()=>{
        const id = btn.getAttribute('data-target');
        const el = document.getElementById(id);
        const text = el ? el.textContent : '';
        navigator.clipboard.writeText(text).then(()=>{
          const old = btn.textContent;
          btn.textContent = 'Copied ✓';
          setTimeout(()=>btn.textContent = old, 1500);
        });
      });
    });
  </script>
</body>
</html>

