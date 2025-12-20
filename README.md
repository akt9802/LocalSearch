# 🔍 LocalSearch++ — A C++ Local Search Engine

LocalSearch++ is a local document search engine built in C++. It indexes text files from a directory and supports fast keyword search, TF-IDF ranking, and exact phrase search using inverted indexing.

This project demonstrates core backend and systems engineering concepts used in real-world search engines.

---

## 🚀 Key Features

- **📁 Recursive File Crawling** – Automatically discovers `.txt` files from directories
- **🔤 Text Tokenization** – Normalization, lowercasing, stopword removal
- **🧠 Inverted Index** – Fast keyword-to-document mapping
- **📊 TF-IDF Ranking** – Relevance-based document scoring
- **🧾 Phrase Search** – Exact phrase matching using positional inverted index
- **💾 Persistent Storage** – Flat-file index saved to disk
- **⚡ Fast Startup** – Load index from disk without re-indexing
- **🖥️ CLI Tool** – Separate index and search modes

---

## 🏗️ High-Level Architecture

```
Documents (.txt)
      ↓
File Crawler
      ↓
Tokenizer
      ↓
Inverted Index ──→ TF-IDF Ranking
      ↓
Positional Index ──→ Phrase Search
      ↓
Flat Files (Persistence)
```

---

## 📂 Project Structure

```
LocalSearch++/
├── data/
│   ├── docs/              # Input documents
│   └── index/             # Saved index files
│       ├── docs.meta
│       ├── inverted.idx
│       └── positional.idx
│
├── src/
│   ├── crawler/           # File crawling logic
│   ├── utils/             # Tokenization utilities
│   ├── indexer/           # Index data structures
│   ├── search/            # Search & ranking logic
│   └── main.cpp           # CLI entry point
│
└── README.md
```

---

## 🧪 Supported Functionalities

### 1️⃣ Keyword Search

Search documents containing given words.

```bash
./localsearch search "google inverted index"
```

Results are ranked using **TF-IDF**.

### 2️⃣ Phrase Search

Search documents containing exact word sequences.

```bash
./localsearch phrase "inverted index"
```

Uses **positional inverted indexing** to ensure adjacency.

### 3️⃣ Index Persistence

- Index is built **once**
- Stored as **flat files**
- Reloaded **instantly** for future searches

---

## ⚙️ How to Build

### Requirements

- C++17 compatible compiler
- MinGW / g++ (Windows, Linux, WSL)

### Compile

```bash
g++ -std=c++17 \
src/main.cpp \
src/utils/TextUtils.cpp \
src/crawler/FileCrawler.cpp \
src/indexer/DocumentStore.cpp \
src/indexer/InvertedIndex.cpp \
src/indexer/PositionalInvertedIndex.cpp \
src/search/TFIDFSearch.cpp \
src/search/PhraseSearch.cpp \
-o localsearch
```

---

## ▶️ How to Run

### 1️⃣ Build the Index

Indexes all `.txt` files inside a directory.

```bash
./localsearch index data/docs
```

**Output:**
```
Index built successfully
```

### 2️⃣ Keyword Search (TF-IDF Ranked)

```bash
./localsearch search "google inverted index"
```

**Example output:**
```
DocID: 1 | Score: 0.6931
```

### 3️⃣ Phrase Search

```bash
./localsearch phrase "inverted index"
```

**Example output:**
```
DocID: 1 | Path: data/docs/sub/b.txt
```

---

## 📄 Index File Formats (Flat Files)

### `docs.meta`
```
docId|filePath|tokenCount
```

### `inverted.idx`
```
term|docId:frequency,docId:frequency
```

### `positional.idx`
```
term|docId:pos,pos;docId:pos,pos
```

These formats are human-readable and easy to extend.

---

## 🧠 Technical Highlights

| Aspect | Details |
|--------|---------|
| **Time Complexity** | Keyword lookup: O(1) average<br>Phrase search: positional matching |
| **Data Structures** | Hash maps, vectors, positional lists |
| **Ranking Algorithm** | TF-IDF (Term Frequency × Inverse Document Frequency) |
| **Design** | Modular, extensible, CLI-based |
| **Language** | C++ (STL, file I/O, memory-safe design) |

---

## 🎯 Why This Project Matters

This project mirrors the core idea behind **Google Search**, scaled down to local files:

- ✅ Index once, query many times
- ✅ Separate indexing and querying
- ✅ Efficient data structures for retrieval
- ✅ Persistence for real-world usability

It demonstrates **systems thinking**, not just application logic.

---

## 🔮 Possible Extensions

- Multithreaded indexing
- Top-K result optimization using heaps
- Index compression
- Support for more file formats
- Incremental index updates

---

## 👨‍💻 Author

**Aman Kumar**  
B.Tech CSE | IIIT Manipur  
Focused on backend systems and problem-solving

---

## 📜 License

MIT License - feel free to use and modify!

---

⭐ **If you found this useful, consider starring the repo!**