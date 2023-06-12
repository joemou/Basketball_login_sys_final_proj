import requests
import csv
from bs4 import BeautifulSoup

# 下載網頁內容
url = "https://www.basketball-reference.com/leagues/NBA_2022_totals.html"
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

# 將資料寫入CSV檔案
with open('player_data.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(headers)
    writer.writerows(data)

print("資料已成功轉換並儲存為player_data.csv檔案。")
