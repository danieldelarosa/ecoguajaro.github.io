# ECOGUAJARO
Proyecto de grado sobre un prototipo para monitoreo de calidad del aire sobre una aplicación móvil

<!DOCTYPE html>
<html>
<head>
  <style>
    .tank-container {
      width: 400px;
      height: 400px;
      display: flex;
      flex-direction: row;
      align-items: flex-start;
      justify-content: center;
    }

    .tank {
      width: 200px;
      height: 300px;
      background-color: #3498db;
      position: relative;
      border: 5px solid #000;
      border-top: 0;
      border-radius: 10px;
      overflow: hidden;
    }

    .water-level {
      width: 100%;
      background-color: #3498db;
      position: absolute;
      bottom: 0;
      border-bottom-left-radius: 10px;
      border-bottom-right-radius: 10px;
      animation: water-animation 2s infinite alternate;
    }

    @keyframes water-animation {
      0% {
        transform: translateY(0);
      }
      100% {
        transform: translateY(-20px);
      }
    }

    .indicators {
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      height: 300px;
      margin-left: 20px;
    }

    .indicator {
      text-align: center;
      font-weight: bold;
    }
  </style>
</head>
<body>
  <div class="tank-container">
    <div class="tank">
      <div class="water-level" style="height: {{level * 20}}%;">{{level * 20}}%</div>
    </div>
    <div class="indicators">
      <div class="indicator">Nivel 5 (120-150 cm)</div>
      <div class="indicator">Nivel 4 (90-120 cm)</div>
      <div class="indicator">Nivel 3 (60-90 cm)</div>
      <div class="indicator">Nivel 2 (30-60 cm)</div>
      <div class="indicator">Nivel 1 (0-30 cm)</div>
    </div>
  </div>

  <script>
    const tank = document.querySelector('.tank');
    const waterLevel = document.querySelector('.water-level');
    const indicators = document.querySelectorAll('.indicator');

    // Función para actualizar el nivel de agua
    function updateWaterLevel(level) {
      const waterHeight = (level / 5) * 100;
      waterLevel.style.height = waterHeight + '%';
    }

    // Simular un cambio de nivel
    let currentLevel = 1;
    setInterval(() => {
      currentLevel = currentLevel % 5 + 1;
      updateWaterLevel(currentLevel);
    }, 2000);
  </script>
</body>
</html>
