import os
import matplotlib.pyplot as plt

# use the directory where this script actually lives
PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))
WIN_STATS = os.path.join(PROJECT_ROOT, "win_stats.txt")
GAME_LOG = os.path.join(PROJECT_ROOT, "game_log.txt")
RESULTS_PATH = os.path.join(PROJECT_ROOT, "results.png")

print(f"Looking for win_stats.txt at: {WIN_STATS}")

def read_stats():
    wins, losses = 0, 0
    try:
        with open(WIN_STATS) as f:
            for line in f:
                if "PlayerWins" in line:
                    wins = int(line.split(":")[1])
                elif "DealerWins" in line:
                    losses = int(line.split(":")[1])
    except FileNotFoundError:
        print("win_stats.txt not found — play at least one game first.")
    return wins, losses

def plot_stats():
    wins, losses = read_stats()
    labels = ['Player Wins', 'Dealer Wins']
    values = [wins, losses]

    plt.bar(labels, values, color=['green', 'red'])
    plt.title('Blackjack Win Statistics')
    plt.ylabel('Number of Wins')

    plt.savefig(RESULTS_PATH)
    print(f"Saved chart to: {RESULTS_PATH}")

    plt.show()

if __name__ == "__main__":
    plot_stats()
