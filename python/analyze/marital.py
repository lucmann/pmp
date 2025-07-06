#!/usr/bin/env python3

from mpl_toolkits.axes_grid1 import host_subplot
from matplotlib.font_manager import FontProperties
from matplotlib.pyplot import figure
from math import pi
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
import os
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

# 0. 解决中文显示问题
# better confirm which chinese fonts are supported on the system, try
#
# fc-list :lang=zh --format="%{family[0]}\n"
#
# then choose one as font.family below
font = {
    'family': 'FandolSong' if os.name == 'posix' else 'SimHei',
    'weight': 'bold',
    'size': 18,
}

plt.rcParams['font.sans-serif'] = ['FandolSong']  # 指定默认字体
plt.rcParams['axes.unicode_minus'] = False    # 解决负号显示问题

###################################################################
#
# 图1 Pie Figure
#
#

# 1. 读取 Excel 文件
file_path = "中国分地区按性别和婚姻状况分的人口(2023年).xlsx"
data = pd.read_excel(file_path, sheet_name="camscanner_ocr", skiprows=2)  # 跳过前3行非数据行

# 2. 提取全国婚姻状况数据（第一行）
national_data = data.iloc[0]  # 全国数据在首行
print(national_data)
marital_status = {
    "未婚":     national_data["总.1"],  # 注意列名可能因Excel格式变化，需检查实际列名
    "有配偶":   national_data["总.2"],
    "离婚":     national_data["总.3"],
    "丧偶":     national_data["总.4"]
}

# 3. 绘制饼状图
plt.figure(figsize=(10, 6))
plt.pie(
    marital_status.values(),
    labels=marital_status.keys(),
    autopct="%1.1f%%",
    startangle=90,
    colors=["#ff9999", "#66b3ff", "#99ff99", "#ffcc99"],
    explode=(0.05, 0, 0, 0)  # 突出"未婚"部分
)
plt.title("2023年中国15岁及以上人口婚姻状况分布（全国）", fontdict=font)
plt.axis("equal")  # 保证饼图是圆形
plt.tight_layout()
# 保存图片须在 show() 之前
plt.savefig('marital_pie.png')

################################################################################
#
# 图2 聚类分析
#

# 重新设置列名
data.columns = [
    "地区", "15岁及以上人口_总", "15岁及以上人口_男", "15岁及以上人口_女",
    "未婚_总", "未婚_男", "未婚_女",
    "有配偶_总", "有配偶_男", "有配偶_女",
    "离婚_总", "离婚_男", "离婚_女",
    "丧偶_总", "丧偶_男", "丧偶_女"
]

# 计算婚姻状况比例
data["未婚"] = data["未婚_总"] / data["15岁及以上人口_总"]
data["有配偶"] = data["有配偶_总"] / data["15岁及以上人口_总"]
data["离婚"] = data["离婚_总"] / data["15岁及以上人口_总"]
data["丧偶"] = data["丧偶_总"] / data["15岁及以上人口_总"]

# 2. 聚类分析
features = data[["未婚", "有配偶", "离婚", "丧偶"]]
scaler = StandardScaler()
scaled_features = scaler.fit_transform(features)


# 选择k=5进行聚类
k = 5
kmeans = KMeans(n_clusters=k, random_state=42)
clusters = kmeans.fit_predict(scaled_features)
data["聚类分组"] = clusters

# 3. 可视化聚类结果
# --------------------------
# 散点矩阵图（Pair Plot）
features_with_cluster = features.copy()
features_with_cluster["聚类分组"] = clusters
sns.pairplot(
    features_with_cluster,
    hue="聚类分组",
    palette="viridis",
    plot_kws={"alpha": 0.7},
    diag_kind="kde"
)
plt.suptitle("婚姻状况聚类分析（散点矩阵图）")

# 保存图片须在 show() 之前
plt.savefig('marital_cluster.png')

###############################################################################
#
# 图3 雷达图（Radar Chart）
#

cluster_means = data.groupby("聚类分组")[["未婚", "有配偶", "离婚", "丧偶"]].mean()
categories = cluster_means.columns
N = len(categories)
angles = [n / N * 2 * pi for n in range(N)]
angles += angles[:1]

fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, polar=True)
for i in range(k):
    values = cluster_means.iloc[i].values.tolist()
    values += values[:1]
    ax.plot(angles, values, linewidth=1, linestyle='solid', label=f'Cluster {i}')
    ax.fill(angles, values, alpha=0.1)

ax.set_xticks(angles[:-1])
ax.set_xticklabels(categories)
ax.set_title("婚姻状况聚类分析（雷达图）")
plt.legend(bbox_to_anchor=(1.05, 1.05), loc='upper right')
# 保存图片须在 show() 之前
plt.savefig('marital_radar.png')

# 4. 输出聚类分组结果
for cluster in range(k):
    print(f"=== 聚类 {cluster} 包含的地区 ===")
    print(data[data["聚类分组"] == cluster]["地区"].tolist())
    print("\n")

# 输出聚类中心（原始比例）
cluster_centers = scaler.inverse_transform(kmeans.cluster_centers_)
centers_df = pd.DataFrame(
    cluster_centers,
    columns=["未婚", "有配偶", "离婚", "丧偶"]
)
print("聚类中心（比例）：\n", centers_df)

###################################################################################
#
# 图4 堆积柱状图 分析性别和婚姻状况的关系
#
# 1. 数据加载与预处理
data = pd.read_excel(file_path, sheet_name="camscanner_ocr", skiprows=3)

# 清理列名（根据实际Excel结构调整）
data.columns = [
    "地区", "15岁及以上人口_总", "15岁及以上人口_男", "15岁及以上人口_女",
    "未婚_总", "未婚_男", "未婚_女",
    "有配偶_总", "有配偶_男", "有配偶_女",
    "离婚_总", "离婚_男", "离婚_女",
    "丧偶_总", "丧偶_男", "丧偶_女"
]

# 2. 提取全国数据（第一行）
national_data = data.iloc[0]

# 3. 准备绘图数据
categories = ["未婚", "有配偶", "离婚", "丧偶"]
men_counts = [
    national_data["未婚_男"],
    national_data["有配偶_男"],
    national_data["离婚_男"],
    national_data["丧偶_男"]
]
women_counts = [
    national_data["未婚_女"],
    national_data["有配偶_女"],
    national_data["离婚_女"],
    national_data["丧偶_女"]
]

# 4. 绘制堆积柱状图
plt.figure(figsize=(12, 6))

# 男性柱状图（底部）
plt.bar(
    categories, men_counts,
    color='#1f77b4', label='男性',
    edgecolor='white', linewidth=0.7
)

# 女性柱状图（堆叠在男性上方）
plt.bar(
    categories, women_counts,
    bottom=men_counts,  # 设置堆叠基准
    color='#ff7f0e', label='女性',
    edgecolor='white', linewidth=0.7
)

# 5. 添加标签和标题
plt.title("2023年全国婚姻状况男女比例", fontsize=16, pad=20)
plt.xlabel("婚姻状况", fontsize=12)
plt.ylabel("人口数（人）", fontsize=12)
plt.legend(title="性别", fontsize=10, title_fontsize=12)

# 6. 显示数值标签
for i in range(len(categories)):
    total = men_counts[i] + women_counts[i]
    plt.text(i, men_counts[i]//2, f"{men_counts[i]:,}", ha='center', va='center', color='white', fontweight='bold')
    plt.text(i, men_counts[i] + women_counts[i]//2, f"{women_counts[i]:,}", ha='center', va='center', color='white', fontweight='bold')
    plt.text(i, total, f"总计\n{total:,}", ha='center', va='bottom', fontsize=9)

# 7. 调整布局并保存
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig("marital_bar.png", dpi=300, bbox_inches='tight')
plt.show()

