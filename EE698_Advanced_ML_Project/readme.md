# 1. Project Overview:

- This project implements an English Grapheme-to-Phoneme (G2P) system using an RNN-Transducer (RNN-T) architecture.
- It models the sequence-to-sequence relationship between English words and their phonetic transcriptions using an encoder-predictor-joiner neural network trained end-to-end.
- We evaluated the system's performance using the Character Error Rate (CER) metric on the CMU Pronouncing Dictionary dataset.

# 2.Sample Examples:

#### Example-1:

- **Input (Grapheme):** `Pronounciation`
- **Predicted Phoneme Output:** ` P R OW N AH N S IY EY SH AH N`

#### Example-2:

- **Input (Grapheme):** `Wednesday`
- **Predicted Phoneme Output:** ` W EH N Z D IY`

#### Example-3:

- **Input (Grapheme):** `Physics`
- **Predicted Phoneme Output:** `F IH Z IH K S`

# 3.How to run the code:

- Run all cells except the cells to save and load the model
- Give input word in predict_word function to get its respective phonemes.

# 4.Authors:

- Kumar Kanishk Singh :sleeping:
- Sunny Raja Prasad :sunglasses:
- Tanmey Agarwal :disguised_face:

# 5.Dataset Used:

- Dataset: CMU Pronouncing Dictionary (via NLTK)

# 6.Model Architecture:

- Encoder: Embedding layer → LSTM → Packed Sequence
- Predictor: Embedding layer → LSTM (with blank token prepending)
- Joiner: Linear projections → ReLU activation → Output layer
- Loss: RNN-Transducer (RNN-T) Loss (torchaudio)
- Applied Beam Search Algorithm during testing to get the best output phonemes of given input word.

# 7.Evaluation:

- Metric: Character Error Rate (CER)
- Results:
  - Training CER: 13.6%
  - Test CER: 14.4%

# 8.References:

- [Transducer Tutorial GitHub Repository](https://github.com/lorenlugosch/transducer-tutorial/tree/main)
- [Interspeech 2022 Paper on Sequence-to-Sequence Learning with Transducers](https://www.isca-archive.org/interspeech_2022/fukuda22_interspeech.pdf)
- [Pretraining Enhanced RNN Transducer (AIR 2024)](https://www.sciopen.com/article/10.26599/AIR.2024.9150039)
- [Ensemble of Grapheme and Phoneme for Machine Transliteration (NLP 2005)](https://aclanthology.org/I05-1040.pdf)
