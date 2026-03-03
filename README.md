# 🎯 SortLab

### ⚡ Интерактивный визуализатор алгоритмов сортировки

![C++](https://img.shields.io/badge/C++-17-00599C?style=flat&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.6-8CC445?style=flat&logo=sfml&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.16+-064F8C?style=flat&logo=cmake&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D4?style=flat&logo=windows&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat)

---

![SortLab Preview](assets/preview.png)

---

## 📖 О проекте

**SortLab** — учебный инструмент для наглядного изучения алгоритмов сортировки.
Каждый элемент массива отображается как столбик. Высота = значение. Цвет = состояние.

Программа показывает работу алгоритма в реальном времени, шаг за шагом, с подсветкой
сравниваемых и переставляемых элементов, счётчиком операций и визуализацией прогресса.

---

## 🧮 Алгоритмы

| # | Алгоритм | Время (лучшее / среднее / худшее) | Память |
|---|---|---|---|
| `1` | 🫧 Bubble Sort | O(n) / O(n²) / O(n²) | O(1) |
| `2` | 🔍 Selection Sort | O(n²) / O(n²) / O(n²) | O(1) |
| `3` | 🃏 Insertion Sort | O(n) / O(n²) / O(n²) | O(1) |
| `4` | 🔀 Merge Sort | O(n log n) / O(n log n) / O(n log n) | O(n) |
| `5` | ⚡ Quick Sort | O(n log n) / O(n log n) / O(n²) | O(log n) |

---

## 🎮 Управление

| Клавиша | Действие |
|---|---|
| `Space` | ▶️ Старт / ⏸️ Пауза |
| `R` | 🔀 Перемешать массив |
| `→` | 👣 Один шаг (в режиме паузы) |
| `↑` / `↓` | 🐇 / 🐢 Увеличить / уменьшить скорость |
| `1` — `5` | 🔢 Выбрать алгоритм |
| `I` | ℹ️ Справка о программе |
| `Q` | 🚪 Выход |

---

## 🖥️ Интерфейс

```
┌─────────────────────────────────────────────────────────────────┐
│ 📊 Algorithm: Quick Sort   Time: O(n log n)   Comparisons: 1.2k │  ← UI панель
├────────────────────────────────────┬────────────────────────────┤
│                                    │                            │
│         📈 Столбики массива        │   🗺️ Progress Map         │
│                                    │                            │
├────────────────────────────────────┴────────────────────────────┤
│  📉 Δ Comparisons / step  [гистограмма]                         │  ← нижняя панель
└─────────────────────────────────────────────────────────────────┘
```

- 📊 **Главная область** — столбики с цветовой индикацией состояний
- 🗺️ **Progress Map** — миниатюрная сетка всего массива, зеленеет по мере сортировки
- 📉 **Гистограмма** — количество сравнений на каждом шаге (пульс алгоритма)

### 🎨 Цветовая схема

| Цвет | Состояние |
|---|---|
| 🔵 Синий | Обычный элемент |
| 🩵 Голубой | Сравниваемые элементы |
| 🟠 Оранжевый | Переставляемые элементы |
| 🟢 Зелёный | Отсортированный элемент |

---

## 🔧 Сборка

### 📦 Зависимости
- 🛠️ [CMake](https://cmake.org/download/) ≥ 3.16
- 💻 [Visual Studio 2022](https://visualstudio.microsoft.com/) с компонентом **Desktop development with C++**
- 🌐 Git (для FetchContent — SFML скачивается автоматически)

### 🚀 Установка

```bash
git clone https://github.com/your-username/SortLab.git
cd SortLab
cmake -S . -B build
cmake --build build --config Release
.\build\Release\SortLab.exe
```

> 💡 SFML 2.6 скачивается и компилируется автоматически при первой сборке.
> ⏱️ Первый запуск `cmake -S . -B build` займёт 1–3 минуты.

---

## 📜 Лицензия

```
MIT 
```

---

<div align="center">
  <sub>🎓 made for college coursework &nbsp;|&nbsp; built with ❤️ by <b>kolo</b></sub>
</div>
