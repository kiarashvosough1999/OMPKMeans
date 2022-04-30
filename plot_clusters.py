import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns


plt.figure()

filename = ""

df = pd.read_csv(f"/{filename}")

cluster_size = max(df[df.columns[-1]])

sns.scatterplot(x=df.a, y=df.b,
                hue=df.c,
                palette=sns.color_palette("hls", n_colors=cluster_size))
plt.xlabel("Dimension 1 Axis")
plt.ylabel("Dimension 2 Axis")
plt.title("Clustered: spending (y) vs income (x)")

plt.show()
