import requests
import csv
from bs4 import BeautifulSoup
import json

# 定義球隊名稱對應的縮寫和全名
team_mapping = {
    "BOS": "Boston_Celtics",
    "BRK": "Brooklyn_Nets",
    "NYK": "New_York_Knicks",
    "PHI": "Philadelphia_76ers",
    "TOR": "Toronto_Raptors",
    "CHI": "Chicago_Bulls",
    "DET": "Detroit_Pistons",
    "MIL": "Milwaukee_Bucks",
    "CHO": "Charlotte_Hornets",
    "MIA": "Miami_Heat",
    "DEN": "Denver_Nuggets",
    "GSW": "Golden_State_Warriors",
    "LAC": "Los_Angeles_Clippers",
    "LAL": "Los_Angeles_Lakers",
    "HOU": "Houston_Rockets",
    "MEM": "Memphis_Grizzlies",
    "SAS": "San_Antonio_Spurs"
}

# 下載網頁內容
url = "https://www.basketball-reference.com/leagues/NBA_2023_totals.html"
response = requests.get(url)
content = response.text

# 解析網頁資料
soup = BeautifulSoup(content, 'html.parser')
table = soup.find('table', {'id': 'totals_stats'})
header_row = table.find('thead').find('tr')
data_rows = table.find('tbody').find_all('tr')

# 提取表頭
headers = []
for th in header_row.find_all('th'):
    headers.append(th.text)

# 提取資料
data = []
count = 1
for row in data_rows:
    row_data = [count]
    for td in row.find_all('td'):
        row_data.append(td.text)
    data.append(row_data)
    count += 1

# 將資料寫入 CSV 檔案
with open('player_data.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(headers)
    writer.writerows(data)

print("資料已成功轉換並儲存為player_data.csv檔案。")

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
        "Team Name": team_name,
        "Players": team_players
    })

# 儲存為 JSON 檔案
with open('data.json', 'w') as file:
    json.dump(json_data, file, indent=4)

print("資料已成功轉換並儲存為data.json檔案。")
