import csv
import json

# 定義球隊名稱對應的縮寫和全名
team_mapping = {
    "BOS": "Boston_Celtics",
    "BRK": "Brooklyn Nets",
    "NYK": "New York Knicks",
    "PHI": "Philadelphia 76ers",
    "TOR": "Toronto Raptors",
    "CHI": "Chicago Bulls",
    "DET": "Detroit Pistons",
    "MIL": "Milwaukee Bucks",
    "CHO": "Charlotte Hornets",
    "MIA": "Miami Heat",
    "DEN": "Denver Nuggets",
    "GSW": "Golden State Warriors",
    "LAC": "Los Angeles Clippers",
    "LAL": "Los Angeles Lakers",
    "HOU": "Houston Rockets",
    "MEM": "Memphis Grizzlies",
    "SAS": "San Antonio Spurs"
}

# 讀取 CSV 檔案
with open('player_data.csv', 'r') as file:
    csv_reader = csv.DictReader(file)
    players_data = list(csv_reader)

# 篩選出指定的球隊
selected_teams = list(team_mapping.keys())
selected_players = []

for player in players_data:
    if player['Tm'] in selected_teams:
        selected_players.append(player)

# 轉換成指定的 JSON 格式
json_data = {
    "Basket_Ball_Teams": []
}


for team_abbr, team_name in team_mapping.items():
    team_players = []
    for player in selected_players:
        if player['Tm'] == team_abbr:
            team_players.append({
                "Name": player['Player'],
                "GP": int(player['G']) if player['G'] != '' else 0,
                "3P": float(player['3P%']) if player['3P%'] != '' else 0.0,
                "PPG": float(player['PTS']) / int(player['G']) if player['PTS'] != '' and player['G'] != '' else 0.0,
                "FG": float(player['FG%']) if player['FG%'] != '' else 0.0,
                "SPG": float(player['STL']) / int(player['G']) if player['STL'] != '' and player['G'] != '' else 0.0
            })

    json_data["Basket_Ball_Teams"].append({
        "Team Name": team_name.replace(" ", "_"),
        "Players": team_players
    })

# 儲存為 JSON 檔案
with open('data.json', 'w') as file:
    json.dump(json_data, file, indent=4)
