from sentence_transformers import SentenceTransformer
from sklearn.metrics.pairwise import cosine_similarity

# Load AI model
model = SentenceTransformer("all-MiniLM-L6-v2")

# Read both documents
with open("document1.txt", "r") as f:
    doc1 = f.read()

with open("document2.txt", "r") as f:
    doc2 = f.read()

# Convert documents into embeddings
embedding1 = model.encode([doc1])
embedding2 = model.encode([doc2])

# Calculate similarity
score = cosine_similarity(embedding1, embedding2)[0][0] * 100

# Save AI score
with open("ai_result.txt", "w") as f:
    f.write(f"{score:.2f}")

