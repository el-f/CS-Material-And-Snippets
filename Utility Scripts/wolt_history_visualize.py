import sys
import json
import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

# Get the JSON file path from command line arguments
if len(sys.argv) != 2:
    print("Usage: python script.py path_to_your_history_json_file.json")
    sys.exit(1)

json_path = sys.argv[1]

# Load the JSON data
with open(json_path, 'r', encoding='utf-8') as file:
    history = json.load(file)

# Helper function to convert total amount to number
def total_amount_to_number(total_amount, currency_symbol='₪'):
    if total_amount == '--': return 0
    parsed = float(total_amount.replace(currency_symbol, '').replace(',', ''))
    return parsed if not pd.isna(parsed) else 0

# Create a DataFrame from the order history
orders = history['orders']
for order in orders:
    order['total_amount_num'] = total_amount_to_number(order['total_amount'])
    order['payment_time'] = datetime.fromtimestamp(order['payment_time_ts'] / 1000)

df = pd.DataFrame(orders)

# Extracting necessary data for visualization
df['year_month'] = df['payment_time'].dt.to_period('M')
df['year'] = df['payment_time'].dt.year

# Total amount spent per month
monthly_summary = df.groupby('year_month')['total_amount_num'].sum()

# Total amount spent per year
yearly_summary = df.groupby('year')['total_amount_num'].sum()

# Distribution of orders by venue
venue_summary = df.groupby('venue_name')['total_amount_num'].sum().sort_values(ascending=False)

# Most expensive and cheapest orders
most_expensive_order = df.loc[df['total_amount_num'].idxmax()]
cheapest_order = df.loc[df[df['total_amount_num'] > 0]['total_amount_num'].idxmin()]

# Plotting
plt.figure(figsize=(14, 7))

# Total amount spent per month
plt.subplot(2, 2, 1)
monthly_summary.plot(kind='bar')
plt.title('Total Amount Spent Per Month')
plt.ylabel('Total Amount (₪)')
plt.xlabel('Month')

# Total amount spent per year
plt.subplot(2, 2, 2)
yearly_summary.plot(kind='bar')
plt.title('Total Amount Spent Per Year')
plt.ylabel('Total Amount (₪)')
plt.xlabel('Year')

# Distribution of orders by venue
plt.subplot(2, 2, 3)
venue_summary.plot(kind='bar', color='orange')
plt.title('Total Amount Spent by Venue')
plt.ylabel('Total Amount (₪)')
plt.xlabel('Venue')
plt.xticks(rotation=90)

# Full breakdown of all order prices
plt.subplot(2, 2, 4)
plt.hist(df['total_amount_num'], bins=20, color='purple')
plt.title('Distribution of Order Prices')
plt.ylabel('Number of Orders')
plt.xlabel('Order Price (₪)')

# Summary Table
summary = {
    'total_orders': len(df),
    'sum_of_total_orders': df['total_amount_num'].sum(),
    'first_order_date': df['payment_time'].min(),
    'last_order_date': df['payment_time'].max(),
    'most_expensive_order': most_expensive_order['total_amount_num'],
    'cheapest_order': cheapest_order['total_amount_num']
}

summary_df = pd.DataFrame(list(summary.items()), columns=['Metric', 'Value'])

# Plot the summary table
fig, ax = plt.subplots(figsize=(8, 2))
ax.axis('tight')
ax.axis('off')
ax.table(cellText=summary_df.values, colLabels=summary_df.columns, cellLoc = 'center', loc='center')


plt.tight_layout()
plt.show()
