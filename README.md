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

Results are ranked using **TF-IDF** (Term Frequency-Inverse Document Frequency).
- **TF** (Term Frequency): Calculated as term count divided by document length
- **IDF** (Inverse Document Frequency): Calculated as log(total_docs / document_frequency)
- Results are sorted in descending order by score

### 2️⃣ Phrase Search

Search documents containing exact word sequences (minimum 2 words required).

```bash
./localsearch phrase "inverted index"
```

Uses **positional inverted indexing** to ensure word adjacency:
- Records the position of each term in every document
- Verifies that subsequent words appear at consecutive positions
- Returns matching documents with their file paths

### 3️⃣ Index Persistence

- Index is built **once**
- Stored as **flat files** in human-readable format
- Reloaded **instantly** for future searches without re-indexing

---

## ⚙️ How to Build

### Requirements

- C++17 compatible compiler (g++, clang, MSVC)
- MinGW / g++ recommended (Windows, Linux, WSL)
- Standard C++ library (STL)

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

Or compile with optimization flags:

```bash
g++ -std=c++17 -O2 \
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

Indexes all `.txt` files inside a directory recursively.

```bash
./localsearch index data/docs
```

**Output:**
```
Index built successfully
```

**Process:**
1. Crawls directory for `.txt` files
2. Tokenizes each file with stopword removal
3. Builds inverted and positional indices
4. Saves three index files: `docs.meta`, `inverted.idx`, `positional.idx`

### 2️⃣ Keyword Search (TF-IDF Ranked)

Search for documents using one or more keywords.

```bash
./localsearch search "google inverted index"
```

**Example output:**
```
--- TF-IDF RESULTS ---
DocID: 1 | Score: 0.6931
DocID: 3 | Score: 0.4055
```

**How it works:**
- Query terms are tokenized without stopword filtering
- For each term, retrieves document frequency and term frequency per document
- Calculates TF-IDF score: (term_count / doc_length) × log(total_docs / doc_frequency)
- Results sorted by score in descending order

### 3️⃣ Phrase Search

Search for documents containing an exact sequence of words (minimum 2 words).

```bash
./localsearch phrase "inverted index"
```

**Example output:**
```
--- PHRASE SEARCH RESULTS ---
DocID: 1 | Path: data/docs/sub/b.txt
```

**How it works:**
- Tokenizes the phrase without stopword filtering
- Finds all documents containing the first word
- For subsequent words, verifies they appear at consecutive positions
- Returns matching documents with their file paths

---

## � Core Components

### File Crawler (`src/crawler/`)
- **FileCrawler**: Recursively discovers `.txt` files from a specified directory
- Returns a list of file paths for indexing

### Text Processing (`src/utils/`)
- **TextUtils**: Handles tokenization, lowercasing, and stopword removal
- Built-in stopwords: "the", "is", "and", "a", "of"

### Indexing (`src/indexer/`)
- **DocumentStore**: Manages document metadata and lookup
- **InvertedIndex**: Maps terms to documents and frequencies (for TF-IDF)
- **PositionalInvertedIndex**: Maps terms to document-position pairs (for phrase search)

### Search & Ranking (`src/search/`)
- **TFIDFSearch**: Keyword search with TF-IDF ranking
  - Tokenizes query without stopword filtering
  - Calculates scores using TF × IDF formula
  - Returns results sorted by relevance score
  
- **PhraseSearch**: Exact phrase matching
  - Requires minimum 2-word phrases
  - Validates positional adjacency across all terms
  - Returns matching documents with file paths

---

## 📄 Index File Formats (Flat Files)

### `docs.meta`
```
docId|filePath|tokenCount
```
Stores metadata for each indexed document including the document ID, file path, and token count (document length).

### `inverted.idx`
```
term|docId:frequency,docId:frequency
```
Maps each term to documents containing it with their term frequencies. Used for keyword search and TF-IDF ranking.

### `positional.idx`
```
term|docId:pos,pos;docId:pos,pos
```
Maps each term to its positions within each document. Used for phrase search to verify word adjacency.

These formats are human-readable and easy to extend.

---

## 🧠 Technical Highlights

| Aspect | Details |
|--------|---------|
| **Time Complexity** | Index building: O(N × M) where N = files, M = avg tokens/file<br>Keyword lookup: O(K) where K = query terms<br>Phrase search: O(D × P) where D = docs, P = avg positions/term |
| **Space Complexity** | O(V × D) where V = unique terms, D = documents |
| **Data Structures** | `std::unordered_map` for term/doc mappings<br>`std::vector` for position tracking<br>Hash-based lookup for O(1) average access |
| **Index Format** | Pipe-delimited flat files (human-readable)<br>Easy to parse and extend |
| **Ranking Algorithm** | TF-IDF: (term_freq / doc_length) × log(total_docs / doc_freq) |
| **Tokenization** | Lowercasing, whitespace/punctuation splitting, stopword removal |
| **Design** | Modular, single-responsibility per class<br>Separation of indexing and querying<br>CLI-based interface |
| **Language** | C++17 with STL<br>Standard file I/O<br>No external dependencies |

---

## 📝 Stopwords

The following common words are removed during tokenization to reduce index size and improve relevance:

```
the, is, and, a, of
```

**Note:** These stopwords are currently hardcoded in [src/main.cpp](src/main.cpp#L14-L18). For custom stopwords, consider loading from the `data/stopwords.txt` file.

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

- **Multithreaded Indexing** – Parallelize file crawling and tokenization
- **Top-K Results** – Use heaps for efficient limit-K retrieval instead of sorting all results
- **Index Compression** – Implement variable-length encoding or delta compression for flat files
- **Additional File Formats** – Support `.pdf`, `.docx`, `.md` in addition to `.txt`
- **Incremental Updates** – Add/remove documents without full re-indexing
- **Advanced Tokenization** – Stemming, lemmatization, n-grams
- **Boolean Queries** – AND, OR, NOT operators for complex searches
- **Wildcard Search** – Support queries like "test*" or "test?"
- **Fuzzy Matching** – Spell-correction and approximate string matching
- **Web Crawler** – Index web pages instead of local files

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