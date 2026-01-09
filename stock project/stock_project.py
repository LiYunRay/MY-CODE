import sys
import pandas as pd
import numpy as np
import matplotlib
matplotlib.use('Qt5Agg')
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.dates import DateFormatter, DayLocator
import matplotlib.dates as mdates
import matplotlib.patches as mpatches
from matplotlib import ticker
from matplotlib.gridspec import GridSpec

from sklearn.ensemble import RandomForestRegressor
from sklearn.linear_model import LinearRegression
from sklearn.svm import SVR
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error, r2_score

from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, 
    QLabel, QComboBox, QPushButton, QFileDialog, QTabWidget, 
    QGroupBox, QGridLayout, QSplitter, QSizePolicy, QTextEdit,
    QSpinBox, QDoubleSpinBox, QProgressBar, QMessageBox,
    QFrame, QScrollArea, QFormLayout, QCheckBox, QRadioButton,
    QButtonGroup, QListWidget, QListWidgetItem, QStackedWidget
)
from PyQt5.QtCore import Qt, QThread, pyqtSignal, QTimer
from PyQt5.QtGui import QFont, QPalette, QColor, QIcon
from datetime import datetime, timedelta
import gc
import traceback
import warnings

# 抑制警告
warnings.filterwarnings('ignore')

# 设置matplotlib支持中文和字体大小
plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'DejaVu Sans']
plt.rcParams['axes.unicode_minus'] = False
plt.rcParams['font.size'] = 10
plt.rcParams['figure.autolayout'] = True
plt.rcParams['figure.facecolor'] = 'white'
plt.rcParams['axes.facecolor'] = 'white'


class StockStatsVisualizer:
    """统计图表可视化类"""
    def __init__(self, data):
        self.data = data
        self.stats = self.calculate_stats()
    
    def calculate_stats(self):
        if self.data is not None:
            columns_to_analyze = [col for col in self.data.columns if col not in ['日期', '类别']]
            stats = self.data.groupby('股票代码')[columns_to_analyze].agg(['max', 'min', 'mean'])
            return stats
        return None
    
    def plot_all_stocks_comparison(self, column, stat_type):
        """绘制所有股票的对比图（只使用柱状图）"""
        if self.stats is None:
            return None
            
        # 中文统计类型映射为英文（与get_color方法匹配）
        stat_type_map = {'最大值': 'max', '最小值': 'min', '均值': 'mean'}
        stat_type_en = stat_type_map.get(stat_type, 'mean')  # 默认为均值（蓝色）
        
        # 获取数据（使用映射后的英文标识）
        if stat_type_en == 'max':
            data_series = self.stats[column]['max']
        elif stat_type_en == 'min':
            data_series = self.stats[column]['min']
        else:  # 'mean'
            data_series = self.stats[column]['mean']
        
        # 只使用柱状图
        fig = Figure(figsize=(14, 6))
        ax = fig.add_subplot(111)
        fig.subplots_adjust(left=0.08, right=0.95, top=0.92, bottom=0.15)
        
        positions = range(len(data_series.index))
        bar_width = 0.8
        
        # 使用渐变色
        cmap = plt.cm.viridis
        colors = [cmap(i / len(positions)) for i in positions]
        
        bars = ax.bar(positions, data_series, width=bar_width, 
                     label=stat_type, color=colors, edgecolor='black', linewidth=0.5)
        
        # 设置x轴标签
        step = max(1, len(positions) // 20)  # 每20个标签显示一个
        tick_positions = [i for i in positions if i % step == 0]
        tick_labels = [data_series.index[i] for i in tick_positions]
        ax.set_xticks(tick_positions)
        ax.set_xticklabels(tick_labels, rotation=45, ha='right', fontsize=10)
        
        # 设置标题和标签
        ax.set_title(f'所有股票{column}的{stat_type}对比', fontsize=14, fontweight='bold', pad=15)
        ax.set_xlabel('股票代码', fontsize=12, labelpad=10)
        ax.set_ylabel(column, fontsize=12, labelpad=10)
        
        # 添加网格
        ax.grid(True, alpha=0.3, linestyle='--')
        
        # 添加数值标签（只显示较高的值）
        max_val = max(data_series)
        for bar in bars:
            height = bar.get_height()
            if height > max_val * 0.7:  # 只显示大于最大值70%的标签
                ax.text(bar.get_x() + bar.get_width()/2., height,
                       f'{height:.2f}', ha='center', va='bottom',
                       fontsize=9, fontweight='bold')
        
        # 优化图例
        ax.legend(fontsize=10, loc='upper right')
        
        # 设置刻度字体
        ax.tick_params(axis='x', labelsize=10)
        ax.tick_params(axis='y', labelsize=10)
        
        # 设置y轴格式
        ax.yaxis.set_major_formatter(ticker.FuncFormatter(lambda x, p: format(int(x), ',')))
        
        return fig
    
    def get_color(self, stat_type):
        """根据统计类型返回颜色"""
        if stat_type == 'max':
            return '#FF6B6B'  # 红色
        elif stat_type == 'min':
            return '#4ECDC4'  # 青色
        else:  # 'mean'
            return '#45B7D1'  # 蓝色


class StockMovingAverage:
    """移动平均线可视化类"""
    def __init__(self, data):
        self.data = data
    
    def plot_moving_averages(self, stock_code):
        if self.data is None:
            return None
        
        stock_data = self.data[self.data['股票代码'] == stock_code].copy()
        if stock_data.empty:
            return None
        
        stock_data['日期'] = pd.to_datetime(stock_data['日期'])
        stock_data.sort_values('日期', inplace=True)
        
        # 只显示最近100天的数据
        if len(stock_data) > 100:
            stock_data = stock_data.iloc[-100:]
        
        # 计算移动平均线
        stock_data['5_day_MA'] = stock_data['收盘价'].rolling(window=5).mean()
        stock_data['30_day_MA'] = stock_data['收盘价'].rolling(window=30).mean()
        stock_data['60_day_MA'] = stock_data['收盘价'].rolling(window=60).mean()
        
        # 标注黄金交叉和死亡交叉点
        stock_data['golden_cross'] = np.where(
            (stock_data['5_day_MA'].shift(1) < stock_data['30_day_MA'].shift(1)) &
            (stock_data['5_day_MA'] > stock_data['30_day_MA']), 1, 0)
        stock_data['death_cross'] = np.where(
            (stock_data['5_day_MA'].shift(1) > stock_data['30_day_MA'].shift(1)) &
            (stock_data['5_day_MA'] < stock_data['30_day_MA']), 1, 0)
        
        fig = Figure(figsize=(14, 8))
        ax = fig.add_subplot(111)
        fig.subplots_adjust(left=0.08, right=0.95, top=0.92, bottom=0.1)
        
        # 绘制收盘价阴影区域
        ax.fill_between(stock_data['日期'], stock_data['最低价'], stock_data['最高价'], 
                       alpha=0.2, color='gray', label='价格区间')
        
        # 绘制移动平均线
        ax.plot(stock_data['日期'], stock_data['收盘价'], label='收盘价', 
               color='#2C3E50', linewidth=2, alpha=0.8)
        ax.plot(stock_data['日期'], stock_data['5_day_MA'], label='5日移动平均线',
               color='#E74C3C', linewidth=1.5)
        ax.plot(stock_data['日期'], stock_data['30_day_MA'], label='30日移动平均线',
               color='#3498DB', linewidth=1.5)
        ax.plot(stock_data['日期'], stock_data['60_day_MA'], label='60日移动平均线',
               color='#2ECC71', linewidth=1.5)
        
        # 标注黄金交叉点 - 绿色正三角
        golden_cross_data = stock_data[stock_data['golden_cross'] == 1]
        if not golden_cross_data.empty:
            ax.scatter(golden_cross_data['日期'], golden_cross_data['5_day_MA'], 
                      marker='^', color='#27AE60', s=120, 
                      label='黄金交叉', edgecolors='white', linewidth=1.5)
        
        # 标注死亡交叉点 - 红色倒三角
        death_cross_data = stock_data[stock_data['death_cross'] == 1]
        if not death_cross_data.empty:
            ax.scatter(death_cross_data['日期'], death_cross_data['5_day_MA'], 
                      marker='v', color='#E74C3C', s=120, 
                      label='死亡交叉', edgecolors='white', linewidth=1.5)
        
        # 添加图例
        ax.legend(loc='upper left', fontsize=10, framealpha=0.9)
        
        # 设置标题和标签
        ax.set_title(f'股票 {stock_code} - 移动平均线和交叉点', 
                    fontsize=14, fontweight='bold', pad=15)
        ax.set_xlabel('日期', fontsize=12, labelpad=10)
        ax.set_ylabel('价格 (元)', fontsize=12, labelpad=10)
        
        # 添加网格
        ax.grid(True, alpha=0.3, linestyle='--')
        
        # 设置刻度
        ax.tick_params(axis='x', labelsize=10)
        ax.tick_params(axis='y', labelsize=10)
        
        # 格式化日期
        ax.xaxis.set_major_formatter(DateFormatter('%Y-%m-%d'))
        fig.autofmt_xdate(rotation=45, ha='right')
        
        # 设置坐标轴范围
        ax.set_xlim(stock_data['日期'].min(), stock_data['日期'].max())
        
        return fig


class StockMACD:
    """MACD指标可视化类"""
    def __init__(self, data):
        self.data = data
    
    def plot_macd(self, stock_code):
        if self.data is None:
            return None
            
        df = self.data[self.data['股票代码'] == stock_code].copy()
        if df.empty:
            return None
            
        df['日期'] = pd.to_datetime(df['日期'])
        df.sort_values('日期', inplace=True)
        
        # 只显示最近100天的数据
        if len(df) > 100:
            df = df.iloc[-100:]
        
        # 计算MACD指标
        df['EMA12'] = df['收盘价'].ewm(span=12, adjust=False).mean()
        df['EMA26'] = df['收盘价'].ewm(span=26, adjust=False).mean()
        df['DIF'] = df['EMA12'] - df['EMA26']
        df['DEA'] = df['DIF'].ewm(span=9, adjust=False).mean()
        df['MACD'] = 2 * (df['DIF'] - df['DEA'])
        colors = np.where(df['MACD'] >= 0, '#E74C3C', '#2ECC71')  # 红色和绿色
        
        fig = Figure(figsize=(14, 8))
        ax = fig.add_subplot(111)
        fig.subplots_adjust(left=0.08, right=0.95, top=0.92, bottom=0.1)
        
        # 将日期转换为matplotlib可以处理的数值
        dates_num = mdates.date2num(df['日期'])
        
        # 绘制MACD柱状图 - 使用数值日期
        ax.bar(dates_num, df['MACD'], width=0.8, color=colors, 
               label='MACD柱', edgecolor='none', alpha=0.7)
        
        # 绘制DIF和DEA线 - 使用数值日期
        ax.plot(dates_num, df['DIF'], color='#3498DB', linewidth=2, 
               label='DIF线', alpha=0.9)
        ax.plot(dates_num, df['DEA'], color='#9B59B6', linewidth=2, 
               label='DEA线', alpha=0.9)
        
        # 添加零线
        ax.axhline(0, color='#95A5A6', linestyle='-', alpha=0.7, linewidth=1)
        
        # 设置标题和标签
        ax.set_title(f'股票 {stock_code} - MACD指标', 
                    fontsize=14, fontweight='bold', pad=15)
        ax.set_xlabel('日期', fontsize=12, labelpad=10)
        ax.set_ylabel('MACD数值', fontsize=12, labelpad=10)
        
        # 添加图例
        ax.legend(fontsize=10, loc='upper left', framealpha=0.9)
        
        # 添加网格
        ax.grid(True, alpha=0.3, linestyle='--')
        
        # 设置刻度
        ax.tick_params(axis='x', labelsize=10)
        ax.tick_params(axis='y', labelsize=10)
        
        # 格式化日期
        ax.xaxis.set_major_formatter(DateFormatter('%Y-%m-%d'))
        ax.xaxis_date()
        fig.autofmt_xdate(rotation=45, ha='right')
        
        # 设置坐标轴范围
        ax.set_xlim(dates_num.min(), dates_num.max())
        
        # 检测并标记黄金交叉和死亡交叉
        self._mark_golden_death_cross(ax, df, dates_num)
        
        return fig
    
    def _mark_golden_death_cross(self, ax, df, dates_num):
        """标记黄金交叉和死亡交叉"""
        # 检测交叉点
        golden_cross_points = []
        death_cross_points = []
        
        for i in range(1, len(df)):
            # 黄金交叉：DIF从下向上穿过DEA
            if df['DIF'].iloc[i-1] < df['DEA'].iloc[i-1] and df['DIF'].iloc[i] > df['DEA'].iloc[i]:
                golden_cross_points.append(i)
            
            # 死亡交叉：DIF从上向下穿过DEA
            elif df['DIF'].iloc[i-1] > df['DEA'].iloc[i-1] and df['DIF'].iloc[i] < df['DEA'].iloc[i]:
                death_cross_points.append(i)
        
        # 标记黄金交叉（绿色三角形）
        for idx in golden_cross_points:
            ax.plot(dates_num[idx], df['DIF'].iloc[idx], '^', 
                   markersize=12, color='#2ECC71', alpha=0.8, 
                   label='黄金交叉' if idx == golden_cross_points[0] else "")
            
        # 标记死亡交叉（红色三角形）
        for idx in death_cross_points:
            ax.plot(dates_num[idx], df['DIF'].iloc[idx], 'v', 
                   markersize=12, color='#E74C3C', alpha=0.8,
                   label='死亡交叉' if idx == death_cross_points[0] else "")
        
        # 添加交叉图例（如果存在交叉点）
        if golden_cross_points or death_cross_points:
            ax.legend(fontsize=10, loc='upper left', framealpha=0.9)


class StockRadar:
    """雷达图可视化类"""
    def __init__(self, data):
        self.data = data
    
    def plot_radar(self, category):
        if self.data is None:
            return None
        
        # 计算所有类别的指标均值（按指标维度分别计算）
        all_categories = self.data['类别'].dropna().unique()
        
        # 存储所有类别的各指标均值
        all_means = {
            '开盘价': [],
            '收盘价': [],
            '交易量': [],
            '换手率': []
        }
        
        # 收集所有类别的各指标均值
        for cat in all_categories:
            cat_data = self.data[self.data['类别'] == cat].copy()
            all_means['开盘价'].append(cat_data['开盘价'].mean())
            all_means['收盘价'].append(cat_data['收盘价'].mean())
            all_means['交易量'].append(cat_data['交易量'].mean())
            all_means['换手率'].append(cat_data['换手率'].mean())
        
        # 获取当前类别的索引
        current_index = list(all_categories).index(category)
        
        # 计算当前类别的原始指标值
        current_category_data = self.data[self.data['类别'] == category].copy()
        avg_open = current_category_data['开盘价'].mean()
        avg_close = current_category_data['收盘价'].mean()
        avg_volume = current_category_data['交易量'].mean()
        avg_turnover = current_category_data['换手率'].mean()
        
        # 对每个指标进行跨类别归一化
        normalized_stats = []
        
        # 开盘价归一化
        open_min = min(all_means['开盘价'])
        open_max = max(all_means['开盘价'])
        if open_max > open_min:
            norm_open = (avg_open - open_min) / (open_max - open_min)
        else:
            norm_open = 0.5
        normalized_stats.append(norm_open)
        
        # 收盘价归一化
        close_min = min(all_means['收盘价'])
        close_max = max(all_means['收盘价'])
        if close_max > close_min:
            norm_close = (avg_close - close_min) / (close_max - close_min)
        else:
            norm_close = 0.5
        normalized_stats.append(norm_close)
        
        # 交易量归一化
        volume_min = min(all_means['交易量'])
        volume_max = max(all_means['交易量'])
        if volume_max > volume_min:
            norm_volume = (avg_volume - volume_min) / (volume_max - volume_min)
        else:
            norm_volume = 0.5
        normalized_stats.append(norm_volume)
        
        # 换手率归一化
        turnover_min = min(all_means['换手率'])
        turnover_max = max(all_means['换手率'])
        if turnover_max > turnover_min:
            norm_turnover = (avg_turnover - turnover_min) / (turnover_max - turnover_min)
        else:
            norm_turnover = 0.5
        normalized_stats.append(norm_turnover)
        
        # 设置雷达图的角度和标签
        labels = ['开盘价均值', '收盘价均值', '交易量均值', '换手率均值']
        num_vars = len(labels)
        
        # 计算每个轴的角度
        angles = np.linspace(0, 2 * np.pi, num_vars, endpoint=False).tolist()
        
        # 使图形闭合
        normalized_stats += normalized_stats[:1]
        angles += angles[:1]
        
        # 创建图形
        fig = Figure(figsize=(10, 8))
        ax = fig.add_subplot(111, polar=True)
        
        # 调整子图边距
        fig.subplots_adjust(left=0.1, right=0.9, top=0.85, bottom=0.1)
        
        # 绘制雷达图
        ax.plot(angles, normalized_stats, color='#3498DB', linewidth=2, 
               linestyle='solid', marker='o', markersize=8, 
               markerfacecolor='white', markeredgecolor='#3498DB', 
               markeredgewidth=2, label=category)
        
        ax.fill(angles, normalized_stats, color='#3498DB', alpha=0.25)
        
        # 设置标签
        ax.set_xticks(angles[:-1])
        ax.set_xticklabels(labels, fontsize=11, fontweight='bold')
        
        # 设置y轴标签
        ax.set_yticks([0.2, 0.4, 0.6, 0.8, 1.0])
        ax.set_yticklabels(['0.2', '0.4', '0.6', '0.8', '1.0'], fontsize=9)
        
        # 设置网格
        ax.grid(True, alpha=0.3, linestyle='--')
        
        # 设置标题
        ax.set_title(f'{category}类别股票指标雷达图 (归一化)', 
                    size=14, fontweight='bold', pad=20)
        
        # 设置y轴范围为0-1（归一化后的值）
        ax.set_ylim(0, 1.1)
        
        # 添加图例
        ax.legend(loc='upper right', bbox_to_anchor=(1.3, 1.1), fontsize=10)
        
        return fig


class PredictionThread(QThread):
    """预测线程，避免GUI界面卡顿"""
    error_occurred = pyqtSignal(str)
    progress_updated = pyqtSignal(int, str)
    prediction_finished = pyqtSignal(dict, dict, dict, str)  # 添加投资建议
    
    def __init__(self, stock_data, selected_stocks, model_type, n_estimators, max_depth, 
                 min_samples_split, test_size, n_steps):
        super().__init__()
        self.stock_data = stock_data
        self.selected_stocks = selected_stocks
        self.model_type = model_type
        self.n_estimators = n_estimators
        self.max_depth = max_depth
        self.min_samples_split = min_samples_split
        self.test_size = test_size
        self.n_steps = n_steps
        self.predictions = {}
        self.models = {}
        self.accuracies = {}
        self.investment_advice = ""  # 投资建议
        self._is_running = True
    
    def stop(self):
        """停止线程"""
        self._is_running = False
    
    def run(self):
        """线程主函数，添加异常处理"""
        try:
            total_tasks = len(self.selected_stocks)
            
            # 发送初始进度
            self.progress_updated.emit(0, "开始预测...")
            self.msleep(100)
            
            completed_tasks = 0
            
            for stock_code in self.selected_stocks:
                # 检查是否应该停止
                if not self._is_running:
                    break
                    
                # 检查股票是否存在
                if stock_code not in self.stock_data:
                    completed_tasks += 1
                    progress = int(completed_tasks/total_tasks*100)
                    self.progress_updated.emit(progress, f"正在预测股票 {stock_code}...")
                    continue
                
                try:
                    # 进行预测和模型评估
                    prediction_result = self._train_and_predict_model(stock_code, self.n_steps)
                    self.predictions[stock_code] = prediction_result
                    self.models[stock_code] = prediction_result.get('model')
                    self.accuracies[stock_code] = prediction_result.get('accuracy')
                    
                    # 生成投资建议
                    self.investment_advice = self._generate_investment_advice(stock_code, prediction_result)
                    
                    # 手动触发垃圾回收，释放内存
                    gc.collect()
                    
                except Exception as e:
                    error_msg = f"预测 {stock_code} 时出错: {str(e)}"
                    print(error_msg)
                    self.error_occurred.emit(error_msg)
                    self.predictions[stock_code] = None
                    self.models[stock_code] = None
                    self.accuracies[stock_code] = None
                
                # 更新进度
                completed_tasks += 1
                progress = int(completed_tasks/total_tasks*100)
                self.progress_updated.emit(progress, f"正在预测股票 {stock_code}...")
            
            # 最后发送完成信号
            self.progress_updated.emit(100, "预测完成！")
            self.prediction_finished.emit(self.predictions, self.models, self.accuracies, self.investment_advice)
            
        except Exception as e:
            error_msg = f"预测线程发生严重错误: {str(e)}"
            print(error_msg)
            self.error_occurred.emit(error_msg)
    
    def _create_features(self, df):
        """创建特征工程，添加异常处理"""
        try:
            # 检查DataFrame是否为空
            if df.empty:
                raise ValueError("输入数据为空")
            
            # 检查必要的列是否存在
            required_columns = ['开盘价', '收盘价', '最高价', '最低价', '交易量', '换手率']
            missing_columns = [col for col in required_columns if col not in df.columns]
            if missing_columns:
                raise ValueError(f"数据缺少必要的列: {', '.join(missing_columns)}")
            
            # 基础特征
            features = df[required_columns].copy()
            
            # 计算移动平均线
            features['MA5'] = df['收盘价'].rolling(window=5, min_periods=1).mean()
            features['MA10'] = df['收盘价'].rolling(window=10, min_periods=1).mean()
            features['MA20'] = df['收盘价'].rolling(window=20, min_periods=1).mean()
            
            # 计算MACD指标
            features['EMA12'] = df['收盘价'].ewm(span=12, adjust=False).mean()
            features['EMA26'] = df['收盘价'].ewm(span=26, adjust=False).mean()
            features['DIF'] = features['EMA12'] - features['EMA26']
            features['DEA'] = features['DIF'].ewm(span=9, adjust=False).mean()
            features['MACD'] = 2 * (features['DIF'] - features['DEA'])
            
            # 添加滞后特征
            for lag in [1, 2, 3]:
                features[f'收盘价_lag{lag}'] = df['收盘价'].shift(lag)
                features[f'交易量_lag{lag}'] = df['交易量'].shift(lag)
            
            # 添加相对强弱指数 (RSI)
            delta = df['收盘价'].diff()
            gain = (delta.where(delta > 0, 0)).rolling(window=14).mean()
            loss = (-delta.where(delta < 0, 0)).rolling(window=14).mean()
            rs = gain / loss
            features['RSI'] = 100 - (100 / (1 + rs))
            
            # 添加布林带 (Bollinger Bands)
            features['BB_MA20'] = df['收盘价'].rolling(window=20).mean()
            features['BB_UPPER'] = features['BB_MA20'] + 2 * df['收盘价'].rolling(window=20).std()
            features['BB_LOWER'] = features['BB_MA20'] - 2 * df['收盘价'].rolling(window=20).std()
            
            # 添加波动率 (Volatility)
            features['VOLATILITY'] = df['收盘价'].rolling(window=20).std()
            
            # 添加成交量加权平均价格 (VWAP)
            features['VWAP'] = (df['收盘价'] * df['交易量']).cumsum() / df['交易量'].cumsum()
            
            # 填充NaN值
            features = features.fillna(method='bfill').fillna(method='ffill').fillna(0)
            
            return features
        except Exception as e:
            raise Exception(f"创建特征工程失败: {str(e)}")
    
    def _get_model(self):
        """根据用户选择的模型类型返回模型实例"""
        if self.model_type == "随机森林":
            return RandomForestRegressor(
                n_estimators=min(self.n_estimators, 100),
                max_depth=self.max_depth if self.max_depth > 0 else None,
                min_samples_split=self.min_samples_split,
                random_state=42,
                n_jobs=1
            )
        elif self.model_type == "线性回归":
            return LinearRegression(n_jobs=1)
        else:  # SVR
            return SVR(kernel='rbf', C=1.0, gamma='auto')
    
    def _generate_investment_advice(self, stock_code, prediction_result):
        """基于预测结果生成投资建议"""
        try:
            if not prediction_result or 'predictions' not in prediction_result:
                return "无法生成投资建议：预测数据不完整"
            
            predictions_dict = prediction_result['predictions']
            confidence_intervals_dict = prediction_result.get('confidence_intervals', {})
            
            # 使用收盘价预测进行分析
            if '收盘价' not in predictions_dict:
                return "无法生成投资建议：缺少收盘价预测数据"
            
            predictions = predictions_dict['收盘价']
            confidence_intervals = confidence_intervals_dict.get('收盘价', [])
            
            if len(predictions) < 2:
                return "需要至少2天的预测数据来生成投资建议"
            
            # 计算预测趋势
            first_pred = predictions[0]
            last_pred = predictions[-1]
            price_change = last_pred - first_pred
            price_change_percent = (price_change / first_pred) * 100 if first_pred > 0 else 0
            
            # 计算置信区间宽度（使用收盘价预测的置信区间）
            avg_ci_width = 0
            if confidence_intervals:
                try:
                    ci_widths = [high - low for low, high in confidence_intervals]
                    avg_ci_width = np.mean(ci_widths) if ci_widths else 0
                except Exception:
                    avg_ci_width = first_pred * 0.1  # 默认设为价格的10%
            
            # 基于模型准确度评分
            accuracy = prediction_result.get('accuracy', {})
            r2_score_value = 0
            
            # 检查accuracy的结构 - 应该是{"MSE": value, "R²": value}格式
            if isinstance(accuracy, dict):
                # 直接使用R²值
                r2_score_value = accuracy.get('R²', 0)
                # 如果没有R²，尝试其他可能的键名
                if r2_score_value == 0:
                    r2_score_value = accuracy.get('r2', 0)
                    if r2_score_value == 0:
                        r2_score_value = accuracy.get('R2', 0)
            
            # 生成投资建议
            advice = f"📈 股票 {stock_code} 投资建议分析\n\n"
            advice += f"预测趋势：未来{len(predictions)}天预测价格从 {first_pred:.2f} 元到 {last_pred:.2f} 元\n"
            advice += f"价格变化：{price_change:+.2f} 元 ({price_change_percent:+.1f}%)\n"
            advice += f"模型置信度 (R²): {r2_score_value:.3f}\n"
            advice += f"平均置信区间宽度：{avg_ci_width:.2f}\n\n"
            
            # 核心投资建议
            advice += "🎯 投资建议：\n"
            
            if price_change_percent > 5 and r2_score_value > 0.8 and avg_ci_width < first_pred * 0.05:
                advice += "✅ 强烈建议买入 - 预测显示强劲上涨趋势，模型置信度高，风险较低\n"
                advice += "建议：可考虑分批买入，设定止损位在当前价格的-5%处"
            elif price_change_percent > 2 and r2_score_value > 0.6:
                advice += "🟢 建议买入 - 预测显示上涨趋势，模型有一定置信度\n"
                advice += "建议：可小仓位试探，关注后续市场动态"
            elif -2 <= price_change_percent <= 2:
                advice += "🟡 建议观望 - 预测价格变化不大，市场可能处于盘整期\n"
                advice += "建议：等待更明确的市场信号，或考虑其他投资机会"
            elif price_change_percent < -2 and r2_score_value > 0.6:
                advice += "🔴 建议卖出 - 预测显示下跌趋势，模型有一定置信度\n"
                advice += "建议：考虑减仓或设置止损，避免进一步损失"
            else:
                advice += "⚪ 建议谨慎操作 - 预测不确定性较高\n"
                advice += "建议：等待更多信息，或使用小仓位进行试探性操作"
            
            return advice
        except Exception as e:
            return f"生成投资建议时出错: {str(e)}"

    def _train_and_predict_model(self, stock_code, n_steps=5):
        """训练模型并进行多维度多步预测"""
        try:
            # 检查数据完整性
            df = self.stock_data[stock_code].copy()
            if df.empty or '日期' not in df.columns:
                raise ValueError("数据无效")

            # 特征工程
            features = self._create_features(df)
            
            # 定义要预测的目标列
            target_columns = ['收盘价', '开盘价', '最高价', '最低价', '交易量']
            
            # 确保目标列存在
            missing_targets = [col for col in target_columns if col not in df.columns]
            if missing_targets:
                raise ValueError(f"缺少预测目标列: {', '.join(missing_targets)}")
            
            # 数据预处理 - 为每个目标创建训练数据
            predictions_dict = {}
            confidence_intervals_dict = {}
            models_dict = {}
            accuracies_dict = {}
            
            # 数据标准化器字典
            scalers_dict = {}
            
            # 为每个目标变量训练模型
            for target_col in target_columns:
                target = df[target_col]
                
                # 确保特征和目标长度匹配
                min_len = min(len(features), len(target))
                features_target = features.iloc[:min_len].copy()
                target_target = target.iloc[:min_len].copy()
                
                # 创建时间序列数据 (用前一天的特征预测当天的目标)
                X = features_target.iloc[:-1]
                y = target_target.iloc[1:]

                # 确保X和y长度匹配
                min_len = min(len(X), len(y))
                X = X.iloc[:min_len]
                y = y.iloc[:min_len]
                
                if len(X) < 10:  # 确保有足够的数据
                    raise ValueError(f"{target_col}数据量不足，无法进行预测")

                # 数据标准化
                scaler = StandardScaler()
                X_scaled = scaler.fit_transform(X)
                scalers_dict[target_col] = scaler
                
                X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=self.test_size, random_state=42)

                # 训练模型
                model = self._get_model()
                model.fit(X_train, y_train)
                models_dict[target_col] = model

                # 预测测试集用于计算置信区间
                y_pred_test = model.predict(X_test)
                test_residuals = y_test - y_pred_test
                residual_std = np.std(test_residuals)
                confidence_level = 1.96  # 95%置信度
                
                accuracies_dict[target_col] = {
                    "MSE": mean_squared_error(y_test, y_pred_test), 
                    "R²": r2_score(y_test, y_pred_test)
                }
                
                # 多步预测 - 使用递归预测
                predictions = []
                confidence_intervals = []
                
                # 使用最后n个数据点作为初始状态
                last_n_points = min(5, len(features_target))
                
                # 初始化特征矩阵用于多步预测
                current_features = features_target.iloc[-last_n_points:].copy()
                
                for step in range(n_steps):
                    try:
                        # 使用最近的特征进行预测
                        recent_features = current_features.iloc[-1:].copy()
                        
                        # 标准化特征
                        recent_features_scaled = scaler.transform(recent_features)
                        
                        # 预测下一步
                        pred = model.predict(recent_features_scaled)[0]
                        predictions.append(pred)
                        
                        # 计算置信区间
                        ci_low = max(pred - confidence_level * residual_std, 0)  # 确保非负
                        ci_high = pred + confidence_level * residual_std
                        confidence_intervals.append((ci_low, ci_high))
                        
                        # 为下一步预测创建新的特征行
                        if step < n_steps - 1:
                            # 创建新的数据行（基于预测结果和业务逻辑）
                            new_row = self._create_next_feature_row(current_features, target_col, pred, df)
                            
                            # 将新行添加到特征矩阵中
                            current_features = pd.concat([current_features, pd.DataFrame([new_row])], ignore_index=True)
                            
                            # 只保留最近的特征用于下一轮预测
                            if len(current_features) > 20:
                                current_features = current_features.iloc[-20:]
                            
                    except Exception as e:
                        print(f"{target_col}第{step+1}步预测出错: {str(e)}")
                        if predictions:
                            predictions.append(predictions[-1])
                            last_ci = confidence_intervals[-1] if confidence_intervals else (0, 0)
                            confidence_intervals.append(last_ci)
                        else:
                            # 使用最后一个已知值作为默认值
                            predictions.append(df[target_col].iloc[-1])
                            std_val = df[target_col].std()
                            confidence_intervals.append((df[target_col].iloc[-1] - std_val, df[target_col].iloc[-1] + std_val))
                
                predictions_dict[target_col] = predictions
                confidence_intervals_dict[target_col] = confidence_intervals

            # 特征重要性（仅适用于随机森林，以收盘价为代表）
            feature_importance = {}
            if hasattr(models_dict.get('收盘价', {}), 'feature_importances_'):
                feature_importance = dict(zip(X.columns, models_dict['收盘价'].feature_importances_))
            
            # 计算整体模型准确度（使用收盘价作为代表）
            overall_accuracy = {}
            if '收盘价' in accuracies_dict:
                overall_accuracy = accuracies_dict['收盘价']
            else:
                # 如果收盘价不存在，使用第一个可用的准确度
                for target_col, acc in accuracies_dict.items():
                    overall_accuracy = acc
                    break

            return {
                'predictions': predictions_dict,
                'confidence_intervals': confidence_intervals_dict,
                'feature_importance': feature_importance,
                'models': models_dict,
                'scalers': scalers_dict,
                'accuracy': overall_accuracy,  # 使用整体准确度而不是按目标列的字典
                'target_columns': target_columns
            }

        except Exception as e:
            raise Exception(f"训练预测模型失败: {str(e)}")
    
    def _create_next_feature_row(self, current_features, target_col, predicted_value, original_df):
        """基于预测结果创建下一个特征行"""
        # 复制最后一行作为基础
        new_row = current_features.iloc[-1:].copy()
        
        # 根据不同目标列更新相应的值
        if target_col == '收盘价':
            new_row['收盘价'] = predicted_value
            # 基于收盘价推断其他价格（简化逻辑）
            volatility = original_df['最高价'].std() / original_df['收盘价'].mean()
            new_row['开盘价'] = predicted_value * (1 + np.random.normal(0, volatility * 0.1))
            new_row['最高价'] = predicted_value * (1 + abs(np.random.normal(0, volatility * 0.2)))
            new_row['最低价'] = predicted_value * (1 - abs(np.random.normal(0, volatility * 0.2)))
            new_row['交易量'] = original_df['交易量'].mean() * (1 + np.random.normal(0, 0.1))
            
        elif target_col == '开盘价':
            new_row['开盘价'] = predicted_value
            # 基于开盘价推断收盘价和其他价格
            close_offset = np.random.normal(0, original_df['收盘价'].std() * 0.05)
            new_row['收盘价'] = predicted_value + close_offset
            high_offset = abs(np.random.normal(0, original_df['最高价'].std() * 0.03))
            low_offset = abs(np.random.normal(0, original_df['最低价'].std() * 0.03))
            new_row['最高价'] = max(new_row['开盘价'].iloc[0], new_row['收盘价'].iloc[0]) + high_offset
            new_row['最低价'] = min(new_row['开盘价'].iloc[0], new_row['收盘价'].iloc[0]) - low_offset
            new_row['交易量'] = original_df['交易量'].mean() * (1 + np.random.normal(0, 0.1))
            
        elif target_col in ['最高价', '最低价']:
            # 对于高低价，保持合理的价格关系
            base_price = current_features['收盘价'].iloc[-1]
            if target_col == '最高价':
                new_row['最高价'] = predicted_value
                new_row['收盘价'] = base_price * (1 + np.random.normal(0, 0.02))
                new_row['开盘价'] = base_price * (1 + np.random.normal(0, 0.01))
                new_row['最低价'] = min(new_row['开盘价'].iloc[0], new_row['收盘价'].iloc[0]) * (1 - abs(np.random.normal(0, 0.02)))
            else:  # 最低价
                new_row['最低价'] = predicted_value
                new_row['收盘价'] = base_price * (1 + np.random.normal(0, 0.02))
                new_row['开盘价'] = base_price * (1 + np.random.normal(0, 0.01))
                new_row['最高价'] = max(new_row['开盘价'].iloc[0], new_row['收盘价'].iloc[0]) * (1 + abs(np.random.normal(0, 0.02)))
            new_row['交易量'] = original_df['交易量'].mean() * (1 + np.random.normal(0, 0.1))
            
        elif target_col == '交易量':
            new_row['交易量'] = max(0, predicted_value)  # 确保交易量非负
            # 其他价格基于历史波动调整
            base_price = current_features['收盘价'].iloc[-1]
            price_volatility = original_df['收盘价'].std() / original_df['收盘价'].mean()
            new_row['收盘价'] = base_price * (1 + np.random.normal(0, price_volatility * 0.05))
            new_row['开盘价'] = base_price * (1 + np.random.normal(0, price_volatility * 0.03))
            new_row['最高价'] = new_row['收盘价'].iloc[0] * (1 + abs(np.random.normal(0, price_volatility * 0.1)))
            new_row['最低价'] = new_row['收盘价'].iloc[0] * (1 - abs(np.random.normal(0, price_volatility * 0.1)))
        
        # 更新滞后特征
        for lag in [1, 2, 3]:
            lag_col = f'收盘价_lag{lag}'
            if lag_col in new_row.columns:
                if lag == 1:
                    new_row[lag_col] = new_row['收盘价'].iloc[0]
                else:
                    prev_lag = f'收盘价_lag{lag-1}'
                    if prev_lag in new_row.columns:
                        new_row[lag_col] = new_row[prev_lag].iloc[0]
        
        # 更新技术指标（简化处理）
        if 'MA5' in new_row.columns:
            recent_prices = list(current_features['收盘价'].iloc[-4:]) + [new_row['收盘价'].iloc[0]]
            new_row['MA5'] = np.mean(recent_prices[-5:])
        
        # 填充可能的NaN值
        new_row = new_row.fillna(method='ffill').fillna(method='bfill').fillna(0)
        
        return new_row.iloc[0]  # 关键修改：返回Series而不是DataFrame


class UnifiedStockAnalysisApp(QMainWindow):
    """统一界面股票数据分析应用主窗口类"""
    def __init__(self):
        super().__init__()
        self.setWindowTitle("股票数据分析可视化系统")
        self.setGeometry(100, 100, 1400, 900)
        
        # 设置应用样式
        self.setStyleSheet("""
            QMainWindow {
                background-color: #f5f5f5;
            }
            QGroupBox {
                font-weight: bold;
                border: 2px solid #cccccc;
                border-radius: 5px;
                margin-top: 10px;
                padding-top: 10px;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 5px 0 5px;
            }
            QPushButton {
                background-color: #3498db;
                color: white;
                border: none;
                padding: 8px 16px;
                border-radius: 4px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #2980b9;
            }
            QPushButton:pressed {
                background-color: #21618c;
            }
            QPushButton:disabled {
                background-color: #bdc3c7;
                color: #7f8c8d;
            }
            QComboBox {
                padding: 5px;
                border: 1px solid #cccccc;
                border-radius: 4px;
                background-color: white;
            }
            QLabel {
                color: #2c3e50;
            }
            QProgressBar {
                border: 1px solid #cccccc;
                border-radius: 4px;
                text-align: center;
            }
            QProgressBar::chunk {
                background-color: #2ecc71;
                border-radius: 4px;
            }
            QTabWidget::pane {
                border: 1px solid #cccccc;
                background-color: white;
            }
            QTabBar::tab {
                background-color: #ecf0f1;
                padding: 8px 16px;
                margin-right: 2px;
                border-top-left-radius: 4px;
                border-top-right-radius: 4px;
            }
            QTabBar::tab:selected {
                background-color: #3498db;
                color: white;
            }
            QTabBar::tab:hover {
                background-color: #bdc3c7;
            }
        """)
        
        # 初始化数据
        self.data = None
        self.stock_codes = []
        self.categories = []
        self.stock_data = {}
        self.prediction_results = {}
        self.prediction_thread = None
        
        # 当前选中的股票（全局）
        self.current_stock = None
        
        # 创建主部件
        self.main_widget = QWidget()
        self.setCentralWidget(self.main_widget)
        
        # 创建主布局
        self.main_layout = QVBoxLayout(self.main_widget)
        self.main_layout.setContentsMargins(10, 10, 10, 10)
        self.main_layout.setSpacing(10)
        
        # 创建顶部控制面板
        self.create_top_control_panel()
        
        # 创建主内容区域
        self.create_main_content()
        
        # 状态栏
        self.statusBar().showMessage("就绪")
        
        # 设置定时器，定期检查内存使用情况
        self.memory_timer = QTimer(self)
        self.memory_timer.timeout.connect(self.check_memory_usage)
        self.memory_timer.start(30000)
    
    def create_top_control_panel(self):
        """创建顶部控制面板"""
        control_frame = QFrame()
        control_frame.setFrameStyle(QFrame.StyledPanel | QFrame.Raised)
        control_layout = QHBoxLayout(control_frame)
        control_layout.setContentsMargins(15, 10, 15, 10)
        
        # 文件操作区域
        file_group = QGroupBox("数据源")
        file_layout = QHBoxLayout(file_group)
        
        self.file_button = QPushButton("📂 加载Excel文件")
        self.file_button.clicked.connect(self.load_file)
        
        self.file_label = QLabel("未选择文件")
        self.file_label.setStyleSheet("color: #7f8c8d; font-style: italic;")
        
        file_layout.addWidget(self.file_button)
        file_layout.addWidget(self.file_label)
        file_layout.addStretch()
        
        # 添加到主布局
        control_layout.addWidget(file_group)
        
        self.main_layout.addWidget(control_frame)
    
    def create_main_content(self):
        """创建主要内容区域"""
        # 创建堆叠部件，用于切换单股票和多股票模式
        self.content_stack = QStackedWidget()
        
        # 单股票分析页面
        self.single_stock_page = self.create_single_stock_page()
        
        # 股票预测页面
        self.prediction_page = self.create_prediction_page()
        
        self.content_stack.addWidget(self.single_stock_page)
        self.content_stack.addWidget(self.prediction_page)
        
        # 模式切换按钮
        mode_frame = QFrame()
        mode_layout = QHBoxLayout(mode_frame)
        mode_layout.setContentsMargins(0, 5, 0, 5)
        
        self.mode_label = QLabel("分析模式:")
        
        self.mode_single_btn = QRadioButton("单股票分析")
        self.mode_prediction_btn = QRadioButton("股票预测")
        self.mode_single_btn.setChecked(True)
        self.mode_single_btn.toggled.connect(self.on_mode_changed)
        self.mode_prediction_btn.toggled.connect(self.on_mode_changed)
        
        mode_layout.addWidget(self.mode_label)
        mode_layout.addWidget(self.mode_single_btn)
        mode_layout.addWidget(self.mode_prediction_btn)
        mode_layout.addStretch()
        
        self.main_layout.addWidget(mode_frame)
        self.main_layout.addWidget(self.content_stack, 1)
    
    def create_single_stock_page(self):
        """创建单股票分析页面"""
        page = QWidget()
        layout = QVBoxLayout(page)
        
        # 创建分析选项卡
        self.single_tab_widget = QTabWidget()
        
        # 创建各个分析选项卡
        self.create_single_stats_tab()
        self.create_single_moving_avg_tab()
        self.create_single_macd_tab()
        self.create_single_radar_tab()
        
        layout.addWidget(self.single_tab_widget)
        
        return page
    
    def create_prediction_page(self):
        """创建股票预测页面（优化布局拉伸）"""
        page = QWidget()
        layout = QVBoxLayout(page)
        # 设置布局边距和拉伸
        layout.setContentsMargins(10, 10, 10, 10)
        layout.setSpacing(10)
        layout.setStretch(1, 1)  # 第二个子控件（tab_widget）拉伸
        
        # 预测页面标题
        title_label = QLabel("股票价格预测与投资建议系统")
        title_label.setStyleSheet("font-size: 16px; font-weight: bold; color: #2c3e50; padding: 10px;")
        title_label.setAlignment(Qt.AlignCenter)
        layout.addWidget(title_label)
        
        # 创建预测选项卡
        self.prediction_tab_widget = QTabWidget()
        # 设置选项卡的尺寸策略
        self.prediction_tab_widget.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        
        # 创建预测相关选项卡
        self.create_single_prediction_tab()
        self.create_investment_advice_tab()
        
        layout.addWidget(self.prediction_tab_widget, 1)  # 拉伸因子1
        
        return page
    
    def create_single_stats_tab(self):
        """创建单股票统计图表选项卡（修复重复图表）"""
        tab = QWidget()
        self.single_tab_widget.addTab(tab, "📊 基础信息")
        
        layout = QVBoxLayout(tab)
        
        # 控制面板
        control_group = QGroupBox("基础信息设置")
        control_layout = QGridLayout(control_group)
        
        # 添加股票选择器
        stock_label = QLabel("选择股票:")
        self.single_stock_combo = QComboBox()
        self.single_stock_combo.setMinimumWidth(120)
        self.single_stock_combo.currentTextChanged.connect(self.on_stock_changed)
        control_layout.addWidget(stock_label, 0, 0)
        control_layout.addWidget(self.single_stock_combo, 0, 1)
        
        # 指标选择
        column_label = QLabel("选择指标:")
        self.single_column_combo = QComboBox()
        self.single_column_combo.addItems(['开盘价', '收盘价', '最高价', '最低价', '交易量', '换手率'])
        
        # 时间范围选择
        period_label = QLabel("显示天数:")
        self.single_period_spin = QSpinBox()
        self.single_period_spin.setRange(30, 365)
        self.single_period_spin.setValue(60)
        
        # 图表类型标签
        chart_type_label = QLabel("图表类型:")
        chart_type_value = QLabel("📊 柱状图")
        chart_type_value.setStyleSheet("color: #3498db; font-weight: bold;")
        
        control_layout.addWidget(column_label, 1, 0)
        control_layout.addWidget(self.single_column_combo, 1, 1)
        control_layout.addWidget(period_label, 2, 0)
        control_layout.addWidget(self.single_period_spin, 2, 1)
        control_layout.addWidget(chart_type_label, 3, 0)
        control_layout.addWidget(chart_type_value, 3, 1)
        
        # 自动生成按钮
        generate_btn = QPushButton("自动生成柱状图")
        # 确保信号只绑定一次
        try:
            self.single_column_combo.currentTextChanged.disconnect()
        except TypeError:
            pass  # 忽略未连接的信号
        self.single_column_combo.currentTextChanged.connect(self.generate_single_stats_chart)
        
        try:
            self.single_period_spin.valueChanged.disconnect()
        except TypeError:
            pass  # 忽略未连接的信号
        self.single_period_spin.valueChanged.connect(self.generate_single_stats_chart)
        
        try:
            generate_btn.clicked.disconnect()
        except TypeError:
            pass  # 忽略未连接的信号
        generate_btn.clicked.connect(self.generate_single_stats_chart)
        control_layout.addWidget(generate_btn, 4, 0, 1, 2)
        
        # 图表区域
        self.single_stats_chart_widget = QWidget()
        self.single_stats_chart_layout = QVBoxLayout(self.single_stats_chart_widget)
        
        # 使用分割器
        splitter = QSplitter(Qt.Vertical)
        splitter.addWidget(control_group)
        splitter.addWidget(self.single_stats_chart_widget)
        splitter.setSizes([200, 600])
        
        layout.addWidget(splitter)
    
    def generate_single_stats_chart(self):
        """生成单股票统计图表（修复重复生成）"""
        if self.data is None:
            self.statusBar().showMessage("请先加载数据文件")
            return
        
        try:
            # 获取选中的股票
            stock_text = self.single_stock_combo.currentText()
            if not stock_text:
                self.statusBar().showMessage("请选择股票")
                return
            
            stock_code = int(stock_text)
            
            # 强制清理旧图表（确保彻底）
            self._clear_chart_layout(self.single_stats_chart_layout)
            QApplication.processEvents()  # 强制刷新界面，避免旧图表残留
            
            # 获取参数
            column = self.single_column_combo.currentText()
            period = self.single_period_spin.value()
            
            # 获取股票数据
            stock_data = self.stock_data.get(stock_code)
            if stock_data is None:
                self.statusBar().showMessage(f"未找到股票 {stock_code} 的数据")
                return
            
            stock_data = stock_data.copy()
            stock_data['日期'] = pd.to_datetime(stock_data['日期'])
            stock_data.sort_values('日期', inplace=True)
            
            # 限制显示天数
            if len(stock_data) > period:
                stock_data = stock_data.iloc[-period:]
            
            # 创建图表
            fig = Figure(figsize=(14, 7))
            ax = fig.add_subplot(111)
            fig.subplots_adjust(left=0.1, right=0.95, top=0.92, bottom=0.15)
            
            # 将日期转换为字符串格式用于x轴
            date_str = stock_data['日期'].dt.strftime('%m-%d').tolist()
            
            # 创建柱状图
            x_pos = np.arange(len(stock_data))
            bar_width = 0.6
            
            # 根据指标选择颜色
            if column == '收盘价':
                color = '#3498DB'
            elif column == '开盘价':
                color = '#2ECC71'
            elif column == '最高价':
                color = '#E74C3C'
            elif column == '最低价':
                color = '#9B59B6'
            elif column == '交易量':
                color = '#F39C12'
            else:  # 换手率
                color = '#1ABC9C'
            
            bars = ax.bar(x_pos, stock_data[column], width=bar_width, 
                         color=color, edgecolor='white', linewidth=1, alpha=0.8)
            
            # 添加趋势线
            z = np.polyfit(x_pos, stock_data[column], 3)
            p = np.poly1d(z)
            ax.plot(x_pos, p(x_pos), color='#E74C3C', linewidth=2, linestyle='--', 
                   alpha=0.7, label='趋势线')
            
            # 计算统计信息
            mean_val = stock_data[column].mean()
            max_val = stock_data[column].max()
            min_val = stock_data[column].min()
            
            # 添加统计线
            ax.axhline(y=mean_val, color='#2C3E50', linestyle='-', linewidth=1.5, 
                      alpha=0.5, label=f'均值: {mean_val:.2f}')
            ax.axhline(y=max_val, color='#E74C3C', linestyle='--', linewidth=1, 
                      alpha=0.5, label=f'最大值: {max_val:.2f}')
            ax.axhline(y=min_val, color='#2ECC71', linestyle='--', linewidth=1, 
                      alpha=0.5, label=f'最小值: {min_val:.2f}')
            
            # 设置x轴标签
            step = max(1, len(date_str) // 10)
            tick_positions = [i for i in range(0, len(date_str), step)]
            tick_labels = [date_str[i] for i in tick_positions]
            ax.set_xticks(tick_positions)
            ax.set_xticklabels(tick_labels, rotation=45, ha='right', fontsize=10)
            
            # 设置标题和标签
            ax.set_title(f'股票 {stock_code} - {column}柱状图 (最近{period}天)', 
                        fontsize=14, fontweight='bold', pad=15)
            ax.set_xlabel('日期', fontsize=12, labelpad=10)
            ax.set_ylabel(column, fontsize=12, labelpad=10)
            
            # 添加图例
            ax.legend(fontsize=10, loc='upper left', framealpha=0.9)
            
            # 添加网格
            ax.grid(True, alpha=0.3, linestyle='--', axis='y')
            
            # 设置刻度
            ax.tick_params(axis='x', labelsize=10)
            ax.tick_params(axis='y', labelsize=10)
            
            # 添加数值标签
            for i, bar in enumerate(bars):
                if i % max(1, len(bars)//20) == 0:
                    height = bar.get_height()
                    ax.text(bar.get_x() + bar.get_width()/2., height,
                           f'{height:.2f}', ha='center', va='bottom',
                           fontsize=8, fontweight='bold')
            
            # 显示图表（确保只添加一次）
            canvas = FigureCanvas(fig)
            if self.single_stats_chart_layout.count() == 0:
                self.single_stats_chart_layout.addWidget(canvas)
            
            self.statusBar().showMessage(f"已生成股票 {stock_code} 的{column}柱状图")
            
        except Exception as e:
            error_msg = f"生成图表失败: {str(e)}"
            self.statusBar().showMessage(error_msg)
            QMessageBox.warning(self, "错误", error_msg)
            print(f"详细错误:\n{traceback.format_exc()}")
    
    def create_single_moving_avg_tab(self):
        """创建单股票移动平均线选项卡"""
        tab = QWidget()
        self.single_tab_widget.addTab(tab, "📈 移动平均线")
        
        layout = QVBoxLayout(tab)
        
        # 控制面板
        control_group = QGroupBox("移动平均线设置")
        control_layout = QGridLayout(control_group)
        
        # 添加股票选择器
        stock_label = QLabel("选择股票:")
        self.single_ma_stock_combo = QComboBox()
        self.single_ma_stock_combo.setMinimumWidth(120)
        self.single_ma_stock_combo.currentTextChanged.connect(self.on_stock_changed)
        control_layout.addWidget(stock_label, 0, 0)
        control_layout.addWidget(self.single_ma_stock_combo, 0, 1)
        
        ma_label = QLabel("显示均线:")
        ma_layout = QHBoxLayout()
        self.ma5_check = QCheckBox("5日")
        self.ma5_check.setChecked(True)
        self.ma10_check = QCheckBox("10日")
        self.ma20_check = QCheckBox("20日")
        self.ma30_check = QCheckBox("30日")
        self.ma30_check.setChecked(True)
        self.ma60_check = QCheckBox("60日")
        self.ma60_check.setChecked(True)
        ma_layout.addWidget(self.ma5_check)
        ma_layout.addWidget(self.ma10_check)
        ma_layout.addWidget(self.ma20_check)
        ma_layout.addWidget(self.ma30_check)
        ma_layout.addWidget(self.ma60_check)
        ma_layout.addStretch()
        control_layout.addWidget(ma_label, 1, 0)
        control_layout.addLayout(ma_layout, 1, 1)
        
        period_label = QLabel("显示天数:")
        self.ma_period_spin = QSpinBox()
        self.ma_period_spin.setRange(30, 365)
        self.ma_period_spin.setValue(100)
        control_layout.addWidget(period_label, 2, 0)
        control_layout.addWidget(self.ma_period_spin, 2, 1)
        
        generate_btn = QPushButton("生成图表")
        generate_btn.clicked.connect(self.generate_single_moving_avg_chart)
        control_layout.addWidget(generate_btn, 3, 0, 1, 2)
        
        # 图表区域
        self.single_moving_avg_chart_widget = QWidget()
        self.single_moving_avg_chart_layout = QVBoxLayout(self.single_moving_avg_chart_widget)
        
        # 使用分割器
        splitter = QSplitter(Qt.Vertical)
        splitter.addWidget(control_group)
        splitter.addWidget(self.single_moving_avg_chart_widget)
        splitter.setSizes([200, 600])
        
        layout.addWidget(splitter)
    
    def create_single_macd_tab(self):
        """创建单股票MACD选项卡"""
        tab = QWidget()
        self.single_tab_widget.addTab(tab, "📉 MACD指标")
        
        layout = QVBoxLayout(tab)
        
        # 控制面板
        control_group = QGroupBox("MACD设置")
        control_layout = QGridLayout(control_group)
        
        # 添加股票选择器
        stock_label = QLabel("选择股票:")
        self.single_macd_stock_combo = QComboBox()
        self.single_macd_stock_combo.setMinimumWidth(120)
        self.single_macd_stock_combo.currentTextChanged.connect(self.on_stock_changed)
        control_layout.addWidget(stock_label, 0, 0)
        control_layout.addWidget(self.single_macd_stock_combo, 0, 1)
        
        period_label = QLabel("显示天数:")
        self.macd_period_spin = QSpinBox()
        self.macd_period_spin.setRange(30, 365)
        self.macd_period_spin.setValue(100)
        
        generate_btn = QPushButton("生成图表")
        generate_btn.clicked.connect(self.generate_single_macd_chart)
        
        control_layout.addWidget(period_label, 1, 0)
        control_layout.addWidget(self.macd_period_spin, 1, 1)
        control_layout.addWidget(generate_btn, 2, 0, 1, 2)
        
        # 图表区域
        self.single_macd_chart_widget = QWidget()
        self.single_macd_chart_layout = QVBoxLayout(self.single_macd_chart_widget)
        
        # 使用分割器
        splitter = QSplitter(Qt.Vertical)
        splitter.addWidget(control_group)
        splitter.addWidget(self.single_macd_chart_widget)
        splitter.setSizes([150, 650])
        
        layout.addWidget(splitter)
    
    def create_single_radar_tab(self):
        """创建单股票雷达图选项卡"""
        tab = QWidget()
        # 使用Qt内置图标系统，避免emoji显示问题
        radar_icon = QIcon.fromTheme("radar", QIcon.fromTheme("target", QIcon.fromTheme("view-refresh")))
        self.single_tab_widget.addTab(tab, radar_icon, "雷达分析")
        
        layout = QVBoxLayout(tab)
        
        # 控制面板
        control_group = QGroupBox("雷达图设置")
        control_layout = QGridLayout(control_group)
        
        category_label = QLabel("选择类别:")
        self.single_category_combo = QComboBox()
        
        generate_btn = QPushButton("生成雷达图")
        generate_btn.clicked.connect(self.generate_single_radar_chart)
        
        control_layout.addWidget(category_label, 0, 0)
        control_layout.addWidget(self.single_category_combo, 0, 1)
        control_layout.addWidget(generate_btn, 1, 0, 1, 2)
        
        # 图表区域
        self.single_radar_chart_widget = QWidget()
        self.single_radar_chart_layout = QVBoxLayout(self.single_radar_chart_widget)
        
        # 使用分割器
        splitter = QSplitter(Qt.Vertical)
        splitter.addWidget(control_group)
        splitter.addWidget(self.single_radar_chart_widget)
        splitter.setSizes([100, 700])
        
        layout.addWidget(splitter)
    
    def create_single_prediction_tab(self):
        """创建单股票预测选项卡（优化图表显示）"""
        tab = QWidget()
        self.prediction_tab_widget.addTab(tab, "📊 基础预测")
        
        layout = QVBoxLayout(tab)
        
        # 股票选择区域 - 简化布局
        stock_group = QGroupBox("预测设置")
        stock_layout = QHBoxLayout(stock_group)
        
        # 添加股票选择器
        pred_stock_label = QLabel("预测股票:")
        self.prediction_stock_combo = QComboBox()
        self.prediction_stock_combo.setMinimumWidth(120)
        stock_layout.addWidget(pred_stock_label)
        stock_layout.addWidget(self.prediction_stock_combo)
        stock_layout.addStretch()
        
        # 预测按钮区域
        button_layout = QHBoxLayout()
        
        self.predict_btn = QPushButton("🚀 开始预测")
        self.predict_btn.clicked.connect(self.run_single_prediction)
        self.predict_btn.setMinimumWidth(120)
        
        self.stop_pred_btn = QPushButton("⏹️ 停止预测")
        self.stop_pred_btn.clicked.connect(self.stop_prediction)
        self.stop_pred_btn.setEnabled(False)
        self.stop_pred_btn.setMinimumWidth(100)
        
        self.progress_bar = QProgressBar()
        self.progress_bar.setMaximumWidth(300)
        
        self.progress_label = QLabel("准备就绪")
        self.progress_label.setStyleSheet("color: #7f8c8d; font-style: italic;")
        
        button_layout.addWidget(self.predict_btn)
        button_layout.addWidget(self.stop_pred_btn)
        button_layout.addWidget(self.progress_bar)
        button_layout.addWidget(self.progress_label)
        button_layout.addStretch()
        
        # 结果展示区域
        result_group = QGroupBox("预测结果")
        result_layout = QVBoxLayout(result_group)
        
        self.result_text = QTextEdit()
        self.result_text.setReadOnly(True)
        self.result_text.setMaximumHeight(120)  # 减少高度，释放图表空间
        
        result_layout.addWidget(self.result_text)
        
        # 图表区域 - 分为左右两栏
        chart_splitter = QSplitter(Qt.Horizontal)
        
        # 左侧图表区域
        left_chart_group = QGroupBox("预测图表")
        left_chart_layout = QVBoxLayout(left_chart_group)
        left_chart_group.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        
        self.prediction_chart_widget = QWidget()
        self.prediction_chart_widget.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.prediction_chart_layout = QVBoxLayout(self.prediction_chart_widget)
        self.prediction_chart_layout.setContentsMargins(5, 5, 5, 5)
        self.prediction_chart_layout.setSpacing(5)
        
        left_chart_layout.addWidget(self.prediction_chart_widget)
        left_chart_layout.setStretchFactor(self.prediction_chart_widget, 1)
        
        # 右侧结果区域
        right_result_group = QGroupBox("预测结果")
        right_result_layout = QVBoxLayout(right_result_group)
        right_result_group.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        
        self.result_text = QTextEdit()
        self.result_text.setReadOnly(True)
        self.result_text.setStyleSheet("font-size: 12px; padding: 10px; background-color: #f9f9f9;")
        
        right_result_layout.addWidget(self.result_text)
        right_result_layout.setStretchFactor(self.result_text, 1)
        
        # 添加到分割器
        chart_splitter.addWidget(left_chart_group)
        chart_splitter.addWidget(right_result_group)
        chart_splitter.setSizes([600, 400])  # 左右比例 6:4
        
        # 设置整体布局的拉伸因子
        layout.addWidget(stock_group)           # 股票选择：不拉伸
        layout.addLayout(button_layout)       # 按钮面板：不拉伸
        layout.addWidget(chart_splitter, 1)   # 图表分割器：拉伸因子1
        
        # 设置布局的拉伸优先级
        layout.setStretch(0, 0)  # stock_group
        layout.setStretch(1, 0)  # button_layout
        layout.setStretch(2, 1)  # chart_splitter
    
    def create_prediction_charts_tab(self):
        """创建预测图表显示选项卡（独立功能）"""
        tab = QWidget()
        self.prediction_tab_widget.addTab(tab, "📈 预测图表")
        
        layout = QVBoxLayout(tab)
        layout.setContentsMargins(10, 10, 10, 10)
        layout.setSpacing(10)
        
        # 图表显示说明
        info_group = QGroupBox("预测图表显示")
        info_layout = QVBoxLayout(info_group)
        
        info_text = QLabel(
            "📊 此功能显示完整的预测图表分析\n\n"
            "✅ 价格走势预测：显示多维度价格预测趋势\n"
            "✅ 收盘价详情：详细展示收盘价预测结果\n"
            "✅ 交易量分析：预测交易量变化趋势\n"
            "✅ 价格区间：展示每日价格波动范围\n\n"
            "💡 提示：请先在'基础预测'页面完成预测，然后切换到本页面查看图表"
        )
        info_text.setWordWrap(True)
        info_text.setStyleSheet("font-size: 12px; padding: 10px;")
        info_layout.addWidget(info_text)
        
        # 图表显示控制
        control_group = QGroupBox("图表控制")
        control_layout = QHBoxLayout(control_group)
        
        # 股票选择器
        chart_stock_label = QLabel("选择股票:")
        self.chart_stock_combo = QComboBox()
        self.chart_stock_combo.setMinimumWidth(120)
        self.chart_stock_combo.currentTextChanged.connect(self.display_prediction_charts)
        
        # 刷新按钮
        refresh_btn = QPushButton("🔄 刷新图表")
        refresh_btn.clicked.connect(self.display_prediction_charts)
        
        control_layout.addWidget(chart_stock_label)
        control_layout.addWidget(self.chart_stock_combo)
        control_layout.addWidget(refresh_btn)
        control_layout.addStretch()
        
        # 图表显示区域 - 最大化显示空间
        chart_group = QGroupBox("多维度预测图表")
        chart_layout = QVBoxLayout(chart_group)
        chart_group.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        
        self.prediction_charts_widget = QWidget()
        self.prediction_charts_layout = QVBoxLayout(self.prediction_charts_widget)
        self.prediction_charts_layout.setContentsMargins(5, 5, 5, 5)
        self.prediction_charts_layout.setSpacing(5)
        
        chart_layout.addWidget(self.prediction_charts_widget)
        
        # 设置布局拉伸因子
        layout.addWidget(info_group)
        layout.addWidget(control_group)
        layout.addWidget(chart_group, 5)  # 图表区域占据最大空间
        
        # 设置拉伸优先级
        layout.setStretch(0, 0)  # 说明区域
        layout.setStretch(1, 0)  # 控制区域
        layout.setStretch(2, 5)  # 图表区域：最大化显示
    
    def display_prediction_charts(self):
        """在图表显示页面显示预测图表"""
        try:
            # 清除旧图表
            self._clear_chart_layout(self.prediction_charts_layout)
            
            # 获取选中的股票
            stock_text = self.chart_stock_combo.currentText()
            if not stock_text:
                return
            
            stock_code = int(stock_text)
            
            # 检查是否有该股票的预测结果
            if stock_code not in self.prediction_results:
                # 显示提示信息
                no_data_label = QLabel("⚠️ 未找到该股票的预测数据，请先在'基础预测'页面完成预测")
                no_data_label.setStyleSheet("color: #E74C3C; font-size: 14px; padding: 20px;")
                no_data_label.setAlignment(Qt.AlignCenter)
                self.prediction_charts_layout.addWidget(no_data_label)
                return
            
            pred_data = self.prediction_results[stock_code]
            
            # 生成多维度预测图表
            self._generate_full_prediction_charts(stock_code, pred_data)
            
        except Exception as e:
            error_msg = f"显示预测图表失败: {str(e)}"
            error_label = QLabel(error_msg)
            error_label.setStyleSheet("color: #E74C3C; font-size: 12px; padding: 10px;")
            error_label.setAlignment(Qt.AlignCenter)
            self.prediction_charts_layout.addWidget(error_label)
            print(f"详细错误:\n{traceback.format_exc()}")
    
    def _generate_full_prediction_charts(self, stock_code, pred_data):
        """生成完整的预测图表（优化显示效果）"""
        try:
            # 检查预测数据
            if not pred_data or 'predictions' not in pred_data:
                raise ValueError("预测数据无效")
            
            predictions_dict = pred_data['predictions']
            confidence_intervals_dict = pred_data.get('confidence_intervals', {})
            
            # 增大Figure尺寸，提供更好的显示效果
            fig = Figure(figsize=(22, 24))  # 进一步增大尺寸
            gs = GridSpec(6, 2, figure=fig, hspace=0.6, wspace=0.5)  # 增加行数和间距
            
            # 获取实际预测步数
            n_steps = len(next(iter(predictions_dict.values())))
            
            # 生成预测日期
            last_date = self.stock_data[stock_code]['日期'].iloc[-1]
            pred_dates = [last_date + timedelta(days=i+1) for i in range(n_steps)]
            date_labels = [date.strftime('%m-%d') for date in pred_dates]
            
            # 颜色配置
            colors = {
                '收盘价': '#E74C3C',
                '开盘价': '#2ECC71', 
                '最高价': '#F39C12',
                '最低价': '#9B59B6',
                '交易量': '#3498DB'
            }
            
            # 子图1: 价格走势预测（占据更大空间）
            ax1 = fig.add_subplot(gs[0:2, :])  # 占据前两行全部
            
            price_cols = ['收盘价', '开盘价', '最高价', '最低价']
            for col in price_cols:
                if col in predictions_dict:
                    predictions = predictions_dict[col]
                    confidence_intervals = confidence_intervals_dict.get(col, [])
                    
                    # 绘制预测线
                    ax1.plot(date_labels, predictions, color=colors[col], linewidth=3, 
                           marker='o', markersize=8, markerfacecolor='white', 
                           markeredgecolor=colors[col], markeredgewidth=2,
                           label=f'预测{col}')
                    
                    # 绘制置信区间
                    if confidence_intervals:
                        lower_bounds = [ci[0] for ci in confidence_intervals]
                        upper_bounds = [ci[1] for ci in confidence_intervals]
                        ax1.fill_between(date_labels, lower_bounds, upper_bounds, 
                                       alpha=0.2, color=colors[col])
            
            ax1.set_title(f'📈 股票 {stock_code} - 未来{n_steps}天价格走势预测', 
                    fontsize=14, fontweight='bold', pad=15)  # 增大字体
            ax1.set_ylabel('价格 (元)', fontsize=12, labelpad=10)
            ax1.legend(fontsize=11, loc='upper left', framealpha=0.9)
            ax1.grid(True, alpha=0.3, linestyle='--')
            ax1.tick_params(axis='x', labelsize=10, rotation=45)
            ax1.tick_params(axis='y', labelsize=10)
            
            # 子图2: 收盘价预测详情
            if '收盘价' in predictions_dict:
                ax2 = fig.add_subplot(gs[2, 0])
                close_pred = predictions_dict['收盘价']
                close_ci = confidence_intervals_dict.get('收盘价', [])
                
                bars = ax2.bar(date_labels, close_pred, color=colors['收盘价'], 
                             alpha=0.8, edgecolor='white', linewidth=1.5)
                
                # 添加置信区间标记
                if close_ci:
                    for i, (pred, ci) in enumerate(zip(close_pred, close_ci)):
                        ax2.errorbar(i, pred, yerr=[[pred-ci[0]], [ci[1]-pred]], 
                                   fmt='none', color='red', capsize=6, alpha=0.7)
                
                ax2.set_title('收盘价预测详情', fontsize=13, fontweight='bold')
                ax2.set_ylabel('价格 (元)', fontsize=11)
                ax2.grid(True, alpha=0.3, linestyle='--')
                ax2.tick_params(axis='x', labelsize=10, rotation=45)
                ax2.tick_params(axis='y', labelsize=10)
                
                # 添加数值标签
                for bar, pred in zip(bars, close_pred):
                    ax2.text(bar.get_x() + bar.get_width()/2., bar.get_height() + max(close_pred)*0.01,
                           f'{pred:.2f}', ha='center', va='bottom', fontsize=9, fontweight='bold')
            
            # 子图3: 交易量预测
            if '交易量' in predictions_dict:
                ax3 = fig.add_subplot(gs[2, 1])
                volume_pred = predictions_dict['交易量']
                volume_ci = confidence_intervals_dict.get('交易量', [])
                
                bars = ax3.bar(date_labels, volume_pred, color=colors['交易量'], 
                             alpha=0.8, edgecolor='white', linewidth=1.5)
                
                # 添加置信区间标记
                if volume_ci:
                    for i, (pred, ci) in enumerate(zip(volume_pred, volume_ci)):
                        ax3.errorbar(i, pred, yerr=[[pred-ci[0]], [ci[1]-pred]], 
                                   fmt='none', color='blue', capsize=6, alpha=0.7)
                
                ax3.set_title('交易量预测详情', fontsize=13, fontweight='bold')
                ax3.set_ylabel('交易量', fontsize=11)
                ax3.grid(True, alpha=0.3, linestyle='--')
                ax3.tick_params(axis='x', labelsize=10, rotation=45)
                ax3.tick_params(axis='y', labelsize=10)
                
                # 添加数值标签
                for bar, pred in zip(bars, volume_pred):
                    ax3.text(bar.get_x() + bar.get_width()/2., bar.get_height() + max(volume_pred)*0.01,
                           f'{pred:.0f}', ha='center', va='bottom', fontsize=9, fontweight='bold')
            
            # 子图4: 价格区间分析
            ax4 = fig.add_subplot(gs[3, :])
            
            if all(col in predictions_dict for col in ['最高价', '最低价', '开盘价', '收盘价']):
                high_pred = predictions_dict['最高价']
                low_pred = predictions_dict['最低价'] 
                open_pred = predictions_dict['开盘价']
                close_pred = predictions_dict['收盘价']
                
                # 绘制价格区间带状图
                for i in range(n_steps):
                    # 每日价格区间
                    daily_min = min(open_pred[i], close_pred[i], low_pred[i])
                    daily_max = max(open_pred[i], close_pred[i], high_pred[i])
                    
                    ax4.fill_between([i-0.4, i+0.4], [daily_min, daily_min], [daily_max, daily_max], 
                                   alpha=0.3, color='gray', label='价格区间' if i == 0 else "")
                    
                    # 标记开盘收盘价
                    ax4.plot([i], [open_pred[i]], 'o', color=colors['开盘价'], markersize=8, 
                            label='开盘价' if i == 0 else "", markeredgecolor='white', markeredgewidth=1.5)
                    ax4.plot([i], [close_pred[i]], 's', color=colors['收盘价'], markersize=8, 
                            label='收盘价' if i == 0 else "", markeredgecolor='white', markeredgewidth=1.5)
                
                ax4.set_title(f'未来{n_steps}天价格区间分析 (灰色区域为每日价格波动范围)', 
                            fontsize=13, fontweight='bold', pad=12)
                ax4.set_xlabel('预测日期', fontsize=11)
                ax4.set_ylabel('价格 (元)', fontsize=11)
                ax4.set_xticks(range(n_steps))
                ax4.set_xticklabels(date_labels)
                ax4.legend(fontsize=10, loc='upper left', framealpha=0.9)
                ax4.grid(True, alpha=0.3, linestyle='--')
            
            # 子图5: 预测准确性分析
            ax5 = fig.add_subplot(gs[4, :])
            
            accuracy = pred_data.get('accuracy', {})
            if accuracy:
                metrics = list(accuracy.keys())
                r2_scores = [acc.get('R²', 0) for acc in accuracy.values()]
                mse_scores = [acc.get('MSE', 0) for acc in accuracy.values()]
                
                x_pos = np.arange(len(metrics))
                width = 0.35
                
                bars1 = ax5.bar(x_pos - width/2, r2_scores, width, 
                              color='#2ECC71', alpha=0.8, label='R²分数')
                bars2 = ax5.bar(x_pos + width/2, mse_scores, width, 
                              color='#E74C3C', alpha=0.8, label='MSE')
                
                ax5.set_title('各维度预测模型准确性分析', fontsize=13, fontweight='bold')
                ax5.set_xlabel('预测维度', fontsize=11)
                ax5.set_ylabel('分数', fontsize=11)
                ax5.set_xticks(x_pos)
                ax5.set_xticklabels(metrics)
                ax5.legend(fontsize=10)
                ax5.grid(True, alpha=0.3, linestyle='--')
                
                # 添加数值标签
                for bar, score in zip(bars1, r2_scores):
                    ax5.text(bar.get_x() + bar.get_width()/2., bar.get_height() + 0.01,
                           f'{score:.3f}', ha='center', va='bottom', fontsize=8)
            
            # 调整布局
            fig.tight_layout(pad=3.0)
            
            # 显示图表
            canvas = FigureCanvas(fig)
            self.prediction_charts_layout.addWidget(canvas)
            
        except Exception as e:
            raise Exception(f"生成完整预测图表失败: {str(e)}")
    
    def create_investment_advice_tab(self):
        """创建投资建议选项卡"""
        tab = QWidget()
        self.prediction_tab_widget.addTab(tab, "💡 投资建议")
        
        layout = QVBoxLayout(tab)
        
        # 投资建议说明
        info_group = QGroupBox("投资建议说明")
        info_layout = QVBoxLayout(info_group)
        
        info_text = QLabel(
            "本系统基于机器学习模型预测结果，结合以下因素生成投资建议：\n\n"
            "✅ 预测价格趋势（上涨/下跌/震荡）\n"
            "✅ 模型置信度（R²分数）\n"
            "✅ 预测置信区间宽度\n"
            "✅ 价格变化幅度\n\n"
            "投资建议仅供参考，股市有风险，投资需谨慎！"
        )
        info_text.setWordWrap(True)
        info_text.setStyleSheet("font-size: 12px; padding: 10px;")
        
        info_layout.addWidget(info_text)
        
        # 投资建议展示
        advice_group = QGroupBox("投资建议分析")
        advice_layout = QVBoxLayout(advice_group)
        
        self.advice_text = QTextEdit()
        self.advice_text.setReadOnly(True)
        self.advice_text.setMinimumHeight(300)
        self.advice_text.setStyleSheet("font-size: 12px; padding: 10px; background-color: #f9f9f9;")
        
        # 初始显示提示信息
        initial_advice = "💡 请先进行股票预测，系统将自动生成投资建议\n\n"
        initial_advice += "投资建议将基于以下因素：\n"
        initial_advice += "1. 预测价格变化趋势\n"
        initial_advice += "2. 模型预测准确度\n"
        initial_advice += "3. 置信区间宽度\n"
        initial_advice += "4. 风险收益比分析"
        
        self.advice_text.setText(initial_advice)
        
        advice_layout.addWidget(self.advice_text)
        
        # 添加到主布局
        layout.addWidget(info_group)
        layout.addWidget(advice_group, 1)
    
    def generate_single_moving_avg_chart(self):
        """生成单股票移动平均线图表"""
        if self.data is None:
            self.statusBar().showMessage("请先加载数据文件")
            return
        
        try:
            # 获取选中的股票
            stock_text = self.single_ma_stock_combo.currentText()
            if not stock_text:
                self.statusBar().showMessage("请选择股票")
                return
            
            stock_code = int(stock_text)
            
            # 清除旧图表
            self._clear_chart_layout(self.single_moving_avg_chart_layout)
            
            # 获取股票数据
            stock_data = self.stock_data.get(stock_code)
            if stock_data is None:
                self.statusBar().showMessage(f"未找到股票 {stock_code} 的数据")
                return
            
            # 生成移动平均线图表
            ma_visualizer = StockMovingAverage(self.data)
            fig = ma_visualizer.plot_moving_averages(stock_code)
            
            if fig:
                canvas = FigureCanvas(fig)
                self.single_moving_avg_chart_layout.addWidget(canvas)
                self.statusBar().showMessage(f"已生成股票 {stock_code} 的移动平均线图表")
            else:
                self.statusBar().showMessage(f"无法生成股票 {stock_code} 的移动平均线图表")
                
        except Exception as e:
            error_msg = f"生成移动平均线图表失败: {str(e)}"
            self.statusBar().showMessage(error_msg)
            QMessageBox.warning(self, "错误", error_msg)
            print(f"详细错误:\n{traceback.format_exc()}")
    
    def generate_single_macd_chart(self):
        """生成单股票MACD图表"""
        if self.data is None:
            self.statusBar().showMessage("请先加载数据文件")
            return
        
        try:
            # 获取选中的股票
            stock_text = self.single_macd_stock_combo.currentText()
            if not stock_text:
                self.statusBar().showMessage("请选择股票")
                return
            
            stock_code = int(stock_text)
            
            # 清除旧图表
            self._clear_chart_layout(self.single_macd_chart_layout)
            
            # 生成MACD图表
            macd_visualizer = StockMACD(self.data)
            fig = macd_visualizer.plot_macd(stock_code)
            
            if fig:
                canvas = FigureCanvas(fig)
                self.single_macd_chart_layout.addWidget(canvas)
                self.statusBar().showMessage(f"已生成股票 {stock_code} 的MACD图表")
            else:
                self.statusBar().showMessage(f"无法生成股票 {stock_code} 的MACD图表")
                
        except Exception as e:
            error_msg = f"生成MACD图表失败: {str(e)}"
            self.statusBar().showMessage(error_msg)
            QMessageBox.warning(self, "错误", error_msg)
            print(f"详细错误:\n{traceback.format_exc()}")
    
    def generate_single_radar_chart(self):
        """生成单股票雷达图"""
        if self.data is None:
            self.statusBar().showMessage("请先加载数据文件")
            return
        
        try:
            # 获取选中的类别
            category = self.single_category_combo.currentText()
            if not category:
                self.statusBar().showMessage("请选择类别")
                return
            
            # 清除旧图表
            self._clear_chart_layout(self.single_radar_chart_layout)
            
            # 生成雷达图
            radar_visualizer = StockRadar(self.data)
            fig = radar_visualizer.plot_radar(category)
            
            if fig:
                canvas = FigureCanvas(fig)
                self.single_radar_chart_layout.addWidget(canvas)
                self.statusBar().showMessage(f"已生成{category}类别的雷达图")
            else:
                self.statusBar().showMessage(f"无法生成{category}类别的雷达图")
                
        except Exception as e:
            error_msg = f"生成雷达图失败: {str(e)}"
            self.statusBar().showMessage(error_msg)
            QMessageBox.warning(self, "错误", error_msg)
            print(f"详细错误:\n{traceback.format_exc()}")
    
    def _generate_multi_dimension_prediction_chart(self, stock_code, pred_data):
        """生成多维度预测图表（优化纵向显示）"""
        try:
            # 清除旧图表
            self._clear_chart_layout(self.prediction_chart_layout)
            
            # 检查预测数据
            if not pred_data or 'predictions' not in pred_data:
                self.result_text.append("\n⚠️ 预测数据无效，无法生成图表")
                return
            
            # 更新图表显示页面的股票选择器
            self._update_chart_stock_combo(stock_code)
            
            predictions_dict = pred_data['predictions']
            confidence_intervals_dict = pred_data.get('confidence_intervals', {})
            target_columns = pred_data.get('target_columns', ['收盘价', '开盘价', '最高价', '最低价', '交易量'])
            
            # 增大Figure尺寸（纵向优先，适合多子图）
            fig = Figure(figsize=(16, 18))  # 增加纵向高度
            gs = GridSpec(4, 2, figure=fig, hspace=0.4, wspace=0.3)  # 增加行数，增大行间距
            
            # 获取实际预测步数
            n_steps = len(next(iter(predictions_dict.values())))  # 从预测数据获取实际步数
            
            # 生成预测日期
            last_date = self.stock_data[stock_code]['日期'].iloc[-1]
            pred_dates = [last_date + timedelta(days=i+1) for i in range(n_steps)]
            date_labels = [date.strftime('%m-%d') for date in pred_dates]
            
            # 颜色配置
            colors = {
                '收盘价': '#E74C3C',
                '开盘价': '#2ECC71', 
                '最高价': '#F39C12',
                '最低价': '#9B59B6',
                '交易量': '#3498DB'
            }
            
            # 子图1: 价格走势预测（收盘价、开盘价、最高价、最低价）
            ax1 = fig.add_subplot(gs[0:2, :])  # 占据前两行全部，增加纵向空间
            
            price_cols = ['收盘价', '开盘价', '最高价', '最低价']
            for col in price_cols:
                if col in predictions_dict:
                    predictions = predictions_dict[col]
                    confidence_intervals = confidence_intervals_dict.get(col, [])
                    
                    # 绘制预测线
                    ax1.plot(date_labels, predictions, color=colors[col], linewidth=2.5, 
                           marker='o', markersize=6, markerfacecolor='white', 
                           markeredgecolor=colors[col], markeredgewidth=1.5,
                           label=f'预测{col}')
                    
                    # 绘制置信区间（仅对价格）
                    if confidence_intervals:
                        lower_bounds = [ci[0] for ci in confidence_intervals]
                        upper_bounds = [ci[1] for ci in confidence_intervals]
                        ax1.fill_between(date_labels, lower_bounds, upper_bounds, 
                                       alpha=0.15, color=colors[col])
            
                ax1.set_title(f'📈 股票 {stock_code} - 未来{n_steps}天价格走势预测', 
                        fontsize=12, fontweight='bold', pad=10)  # 减小标题字体
            ax1.set_ylabel('价格 (元)', fontsize=10, labelpad=8)  # 减小标签字体
            ax1.legend(fontsize=9, loc='upper left', framealpha=0.9)  # 减小图例字体
            ax1.grid(True, alpha=0.3, linestyle='--')
            ax1.tick_params(axis='x', labelsize=9, rotation=45)  # 减小刻度字体
            ax1.tick_params(axis='y', labelsize=9)  # 减小刻度字体
            
            # 子图2: 收盘价预测详情
            if '收盘价' in predictions_dict:
                ax2 = fig.add_subplot(gs[2, 0])  # 移动到第3行第1列
                close_pred = predictions_dict['收盘价']
                close_ci = confidence_intervals_dict.get('收盘价', [])
                
                bars = ax2.bar(date_labels, close_pred, color=colors['收盘价'], 
                             alpha=0.7, edgecolor='white', linewidth=1)
                
                # 添加置信区间标记
                if close_ci:
                    for i, (pred, ci) in enumerate(zip(close_pred, close_ci)):
                        ax2.errorbar(i, pred, yerr=[[pred-ci[0]], [ci[1]-pred]], 
                                   fmt='none', color='red', capsize=5, alpha=0.6)
                
                ax2.set_title('收盘价预测详情', fontsize=12, fontweight='bold')
                ax2.set_ylabel('价格 (元)', fontsize=10)
                ax2.grid(True, alpha=0.3, linestyle='--')
                ax2.tick_params(axis='x', labelsize=9, rotation=45)
                ax2.tick_params(axis='y', labelsize=9)
                
                # 添加数值标签
                for bar, pred in zip(bars, close_pred):
                    ax2.text(bar.get_x() + bar.get_width()/2., bar.get_height() + max(close_pred)*0.01,
                           f'{pred:.2f}', ha='center', va='bottom', fontsize=8, fontweight='bold')
            
            # 子图3: 交易量预测
            if '交易量' in predictions_dict:
                ax3 = fig.add_subplot(gs[2, 1])  # 移动到第3行第2列
                volume_pred = predictions_dict['交易量']
                volume_ci = confidence_intervals_dict.get('交易量', [])
                
                bars = ax3.bar(date_labels, volume_pred, color=colors['交易量'], 
                             alpha=0.7, edgecolor='white', linewidth=1)
                
                # 添加置信区间标记
                if volume_ci:
                    for i, (pred, ci) in enumerate(zip(volume_pred, volume_ci)):
                        ax3.errorbar(i, pred, yerr=[[pred-ci[0]], [ci[1]-pred]], 
                                   fmt='none', color='blue', capsize=5, alpha=0.6)
                
                ax3.set_title('交易量预测详情', fontsize=12, fontweight='bold')
                ax3.set_ylabel('交易量', fontsize=10)
                ax3.grid(True, alpha=0.3, linestyle='--')
                ax3.tick_params(axis='x', labelsize=9, rotation=45)
                ax3.tick_params(axis='y', labelsize=9)
                
                # 添加数值标签
                for bar, pred in zip(bars, volume_pred):
                    ax3.text(bar.get_x() + bar.get_width()/2., bar.get_height() + max(volume_pred)*0.01,
                           f'{pred:.0f}', ha='center', va='bottom', fontsize=8, fontweight='bold')
            
            # 子图4: 价格区间分析
            ax4 = fig.add_subplot(gs[3, :])  # 移动到第4行全部
            
            if all(col in predictions_dict for col in ['最高价', '最低价', '开盘价', '收盘价']):
                high_pred = predictions_dict['最高价']
                low_pred = predictions_dict['最低价'] 
                open_pred = predictions_dict['开盘价']
                close_pred = predictions_dict['收盘价']
                
                # 绘制价格区间带状图
                for i in range(n_steps):
                    # 每日价格区间
                    daily_min = min(open_pred[i], close_pred[i], low_pred[i])
                    daily_max = max(open_pred[i], close_pred[i], high_pred[i])
                    
                    ax4.fill_between([i-0.4, i+0.4], [daily_min, daily_min], [daily_max, daily_max], 
                                   alpha=0.3, color='gray', label='价格区间' if i == 0 else "")
                    
                    # 标记开盘收盘价
                    ax4.plot([i], [open_pred[i]], 'o', color=colors['开盘价'], markersize=6, 
                            label='开盘价' if i == 0 else "", markeredgecolor='white', markeredgewidth=1)
                    ax4.plot([i], [close_pred[i]], 's', color=colors['收盘价'], markersize=6, 
                            label='收盘价' if i == 0 else "", markeredgecolor='white', markeredgewidth=1)
                
                ax4.set_title(f'未来{n_steps}天价格区间分析 (灰色区域为每日价格波动范围)', 
                            fontsize=12, fontweight='bold', pad=10)
                ax4.set_xlabel('预测日期', fontsize=10)
                ax4.set_ylabel('价格 (元)', fontsize=10)
                ax4.set_xticks(range(n_steps))
                ax4.set_xticklabels(date_labels)
                ax4.legend(fontsize=9, loc='upper left', framealpha=0.9)
                ax4.grid(True, alpha=0.3, linestyle='--')
                ax4.tick_params(axis='x', labelsize=9)
                ax4.tick_params(axis='y', labelsize=9)
            
            # 整体标题
            fig.suptitle(f'🎯 股票 {stock_code} - 多维度{n_steps}天预测分析报告', 
                        fontsize=16, fontweight='bold', y=0.98)
            
            # 调整布局
            fig.subplots_adjust(left=0.08, right=0.95, top=0.92, bottom=0.08)
            
            # 增强Canvas的尺寸策略
            canvas = FigureCanvas(fig)
            canvas.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
            canvas.updateGeometry()
            
            # 添加到布局并设置拉伸因子
            self.prediction_chart_layout.addWidget(canvas)
            self.prediction_chart_layout.setStretchFactor(canvas, 1)
            
            # 强制刷新布局
            self.prediction_chart_widget.update()
            self.prediction_chart_widget.adjustSize()
            
            self.statusBar().showMessage(f"已生成股票 {stock_code} 的多维度预测图表")
            
        except Exception as e:
            error_msg = f"生成多维度预测图表失败: {str(e)}"
            print(error_msg)
            self.result_text.append(f"\n⚠️ {error_msg}")
    
    def _clear_chart_layout(self, layout):
        """增强版图表布局清理函数（彻底清除旧图表）"""
        try:
            # 先暂停界面刷新，避免闪烁
            QApplication.setOverrideCursor(Qt.WaitCursor)
            
            # 循环删除所有子项（包括布局项和控件）
            while layout.count():
                item = layout.takeAt(0)
                # 处理控件项
                widget = item.widget()
                if widget is not None:
                    widget.setParent(None)  # 解除父控件关联
                    widget.deleteLater()    # 延迟删除
                # 处理布局项（嵌套布局）
                elif item.layout() is not None:
                    self._clear_chart_layout(item.layout())
            
            # 强制触发垃圾回收，释放内存
            gc.collect()
            QApplication.processEvents()  # 强制刷新
            
        except Exception as e:
            print(f"清除图表布局时出错: {str(e)}")
        finally:
            # 恢复鼠标光标
            QApplication.restoreOverrideCursor()
    
    def check_memory_usage(self):
        """检查内存使用情况（可选优化）"""
        try:
            import psutil
            process = psutil.Process()
            mem_usage = process.memory_info().rss / 1024 / 1024  # MB
            if mem_usage > 500:  # 超过500MB时清理内存
                gc.collect()
                self.statusBar().showMessage(f"内存使用: {mem_usage:.1f}MB (已执行垃圾回收)")
            else:
                self.statusBar().showMessage(f"内存使用: {mem_usage:.1f}MB")
        except ImportError:
            pass  # 未安装psutil则跳过
        except Exception as e:
            print(f"检查内存使用时出错: {str(e)}")
    
    def load_file(self):
        """加载Excel数据文件"""
        try:
            file_path, _ = QFileDialog.getOpenFileName(
                self, "选择Excel文件", "", "Excel文件 (*.xlsx *.xls);;所有文件 (*.*)"
            )
            
            if not file_path:
                return
            
            self.file_label.setText(f"已加载: {file_path.split('/')[-1]}")
            self.statusBar().showMessage(f"正在加载数据文件: {file_path}")
            
            # 读取Excel文件
            self.data = pd.read_excel(file_path)
            
            # 验证必要的列
            required_columns = ['股票代码', '日期', '开盘价', '收盘价', '最高价', '最低价', '交易量', '换手率']
            missing_columns = [col for col in required_columns if col not in self.data.columns]
            
            if missing_columns:
                QMessageBox.warning(self, "数据格式错误", 
                                   f"缺少必要的列: {', '.join(missing_columns)}")
                self.data = None
                return
            
            # 处理日期列
            self.data['日期'] = pd.to_datetime(self.data['日期'])
            
            # 提取股票代码和类别
            self.stock_codes = sorted(self.data['股票代码'].unique())
            self.categories = sorted(self.data['类别'].dropna().unique()) if '类别' in self.data.columns else []
            
            # 按股票代码分组存储数据
            self.stock_data = {}
            for code in self.stock_codes:
                self.stock_data[code] = self.data[self.data['股票代码'] == code].copy()
            
            # 更新所有下拉框
            self.single_stock_combo.clear()
            self.single_stock_combo.addItems([str(code) for code in self.stock_codes])
            
            self.single_ma_stock_combo.clear()
            self.single_ma_stock_combo.addItems([str(code) for code in self.stock_codes])
            
            self.single_macd_stock_combo.clear()
            self.single_macd_stock_combo.addItems([str(code) for code in self.stock_codes])
            
            self.prediction_stock_combo.clear()
            self.prediction_stock_combo.addItems([str(code) for code in self.stock_codes])
            
            self.single_category_combo.clear()
            self.single_category_combo.addItems(self.categories)
            
            self.statusBar().showMessage(f"成功加载 {len(self.stock_codes)} 只股票的数据")
            QMessageBox.information(self, "成功", f"已加载 {len(self.stock_codes)} 只股票的数据！")
            
        except Exception as e:
            error_msg = f"加载文件失败: {str(e)}"
            self.statusBar().showMessage(error_msg)
            QMessageBox.critical(self, "错误", error_msg)
            print(f"详细错误:\n{traceback.format_exc()}")
    
    def on_stock_changed(self, stock_text):
        """股票选择变化时的处理"""
        if not stock_text:
            self.current_stock = None
            return
        
        try:
            self.current_stock = int(stock_text)
            self.statusBar().showMessage(f"当前选中股票: {self.current_stock}")
        except ValueError:
            self.current_stock = None
    
    def on_mode_changed(self):
        """切换分析模式"""
        if self.mode_single_btn.isChecked():
            self.content_stack.setCurrentWidget(self.single_stock_page)
            self.statusBar().showMessage("当前模式：单股票分析")
        elif self.mode_prediction_btn.isChecked():
            self.content_stack.setCurrentWidget(self.prediction_page)
            self.statusBar().showMessage("当前模式：股票预测")
    
    def run_single_prediction(self):
        """运行单股票预测（默认使用随机森林）"""
        if self.data is None:
            QMessageBox.warning(self, "数据缺失", "请先加载股票数据文件！")
            return
        
        # 获取选中的股票
        stock_text = self.prediction_stock_combo.currentText()
        if not stock_text:
            QMessageBox.warning(self, "选择股票", "请选择要预测的股票！")
            return
        
        stock_code = int(stock_text)
        if stock_code not in self.stock_data:
            QMessageBox.warning(self, "数据错误", f"未找到股票 {stock_code} 的数据！")
            return
        
        # 固定使用随机森林模型，设置默认参数
        model_type = "随机森林"
        n_estimators = 100  # 默认估计器数量
        max_depth = 10      # 默认最大深度
        min_samples_split = 5  # 默认最小分割样本数
        test_size = 0.2     # 默认测试集比例
        n_steps = 7         # 默认预测天数
        
        # 重置UI状态
        self.result_text.clear()
        self.advice_text.clear()
        self.progress_bar.setValue(0)
        self.progress_label.setText("准备预测...")
        
        # 禁用按钮
        self.predict_btn.setEnabled(False)
        self.stop_pred_btn.setEnabled(True)
        
        # 创建预测线程
        self.prediction_thread = PredictionThread(
            self.stock_data, [stock_code], model_type, n_estimators, 
            max_depth, min_samples_split, test_size, n_steps
        )
        
        # 绑定线程信号
        self.prediction_thread.error_occurred.connect(self.on_prediction_error)
        self.prediction_thread.progress_updated.connect(self.on_prediction_progress)
        self.prediction_thread.prediction_finished.connect(self.on_prediction_finished)
        
        # 启动线程
        self.prediction_thread.start()
        self.statusBar().showMessage(f"开始预测股票 {stock_code}...")
        
        # 显示预测信息
        self.result_text.append(f"📊 开始预测股票 {stock_code}\n")
        self.result_text.append(f"模型类型: {model_type} (默认)")
        self.result_text.append(f"预测天数: {n_steps} 天")
        self.result_text.append(f"测试集比例: {test_size:.1%}")
        self.result_text.append(f"随机森林参数: 估计器={n_estimators}, 最大深度={max_depth}, 最小分割={min_samples_split}")
        self.result_text.append("\n请等待预测完成...\n")
    
    def stop_prediction(self):
        """停止预测"""
        if self.prediction_thread and self.prediction_thread.isRunning():
            self.prediction_thread.stop()
            self.progress_label.setText("正在停止预测...")
            self.statusBar().showMessage("正在停止预测...")
    
    def on_prediction_error(self, error_msg):
        """预测错误处理"""
        self.result_text.append(f"\n❌ 预测错误: {error_msg}")
        self.progress_label.setText("预测出错")
        
        # 恢复按钮状态
        self.predict_btn.setEnabled(True)
        self.stop_pred_btn.setEnabled(False)
    
    def on_prediction_progress(self, progress, message):
        """更新预测进度"""
        self.progress_bar.setValue(progress)
        self.progress_label.setText(message)
        self.statusBar().showMessage(message)
    
    def on_prediction_finished(self, predictions, models, accuracies, investment_advice):
        """预测完成处理"""
        # 恢复按钮状态
        self.predict_btn.setEnabled(True)
        self.stop_pred_btn.setEnabled(False)
        
        # 获取选中的股票
        stock_text = self.prediction_stock_combo.currentText()
        stock_code = int(stock_text) if stock_text else None
        
        if not stock_code or stock_code not in predictions:
            self.result_text.append("\n❌ 未获取到预测结果")
            return
        
        pred_data = predictions[stock_code]
        if not pred_data:
            self.result_text.append("\n❌ 预测结果为空")
            return
        
        # 显示预测结果
        self.result_text.append("\n✅ 多维度预测完成！")
        self.result_text.append(f"\n📈 股票 {stock_code} 5天多维度预测结果:")
        
        # 显示各维度的预测数据
        predictions_dict = pred_data.get('predictions', {})
        confidence_intervals_dict = pred_data.get('confidence_intervals', {})
        target_columns = pred_data.get('target_columns', ['收盘价', '开盘价', '最高价', '最低价', '交易量'])
        
        # 生成预测日期
        last_date = self.stock_data[stock_code]['日期'].iloc[-1]
        pred_dates = [last_date + timedelta(days=i+1) for i in range(5)]
        date_labels = [date.strftime('%m-%d') for date in pred_dates]
        
        # 创建美观的表格形式显示预测结果
        self.result_text.append(f"\n{'='*80}")
        self.result_text.append(f"📊 未来5天详细预测数据表")
        self.result_text.append(f"{'='*80}")
        
        # 表头
        header = f"{'日期':<8} {'开盘价(元)':<12} {'收盘价(元)':<12} {'最高价(元)':<12} {'最低价(元)':<12} {'交易量':<12}"
        self.result_text.append(header)
        self.result_text.append("-" * 80)
        
        # 数据行
        for i in range(5):
            date_str = date_labels[i]
            
            # 获取各维度预测值
            open_val = predictions_dict.get('开盘价', [0]*5)[i] if '开盘价' in predictions_dict else 0
            close_val = predictions_dict.get('收盘价', [0]*5)[i] if '收盘价' in predictions_dict else 0
            high_val = predictions_dict.get('最高价', [0]*5)[i] if '最高价' in predictions_dict else 0
            low_val = predictions_dict.get('最低价', [0]*5)[i] if '最低价' in predictions_dict else 0
            vol_val = predictions_dict.get('交易量', [0]*5)[i] if '交易量' in predictions_dict else 0
            
            # 格式化数值
            open_str = f"{open_val:.2f}" if open_val != 0 else "--"
            close_str = f"{close_val:.2f}" if close_val != 0 else "--"
            high_str = f"{high_val:.2f}" if high_val != 0 else "--"
            low_str = f"{low_val:.2f}" if low_val != 0 else "--"
            vol_str = f"{vol_val:.0f}" if vol_val != 0 else "--"
            
            row = f"{date_str:<8} {open_str:<12} {close_str:<12} {high_str:<12} {low_str:<12} {vol_str:<12}"
            self.result_text.append(row)
        
        self.result_text.append("=" * 80)
        
        # 显示置信区间信息
        self.result_text.append(f"\n📊 预测置信区间 (95%置信度):")
        for col in ['收盘价', '开盘价', '最高价', '最低价', '交易量']:
            if col in predictions_dict and col in confidence_intervals_dict:
                self.result_text.append(f"\n{col}预测置信区间:")
                for i, (pred, ci) in enumerate(zip(predictions_dict[col], confidence_intervals_dict[col])):
                    if ci[0] != ci[1]:  # 只有当置信区间有意义时才显示
                        self.result_text.append(f"  第{i+1}天: {pred:.2f} [{ci[0]:.2f}, {ci[1]:.2f}]")
        
        # 显示模型准确度
        accuracy = pred_data.get('accuracy', {})
        if accuracy:
            self.result_text.append(f"\n🎯 模型准确度:")
            if isinstance(accuracy, dict) and 'R²' in accuracy:
                # 兼容旧的多维度字典结构
                for col, acc in accuracy.items():
                    r2 = acc if isinstance(acc, (int, float)) else acc.get('R²', 0)
                    mse = acc.get('MSE', 0) if isinstance(acc, dict) else 0
                    self.result_text.append(f"  {col}: R² = {r2:.4f}, MSE = {mse:.4f}")
            elif isinstance(accuracy, (int, float)):
                # 新的整体 R² 结构
                self.result_text.append(f"  整体 R² = {accuracy:.4f}")
            else:
                self.result_text.append("  无法解析准确度数据")
        
        # 显示投资建议
        self.advice_text.setText(investment_advice)
        
        # 更新状态
        self.progress_label.setText("多维度预测完成")
        self.statusBar().showMessage(f"股票 {stock_code} 多维度预测完成")
        
        # 显示基础预测图表
        self._generate_multi_dimension_prediction_chart(stock_code, pred_data)
    
    def _update_chart_stock_combo(self, new_stock_code):
        """更新图表显示页面的股票选择器"""
        try:
            # 保存当前选中的股票
            current_stock = self.chart_stock_combo.currentText()
            
            # 清空并重新填充股票选择器
            self.chart_stock_combo.clear()
            
            # 添加所有有预测结果的股票
            for stock_code in self.prediction_results.keys():
                self.chart_stock_combo.addItem(str(stock_code))
            
            # 如果有新预测的股票，选择它；否则保持原来的选择
            if new_stock_code in self.prediction_results:
                self.chart_stock_combo.setCurrentText(str(new_stock_code))
            elif current_stock and current_stock in [str(code) for code in self.prediction_results.keys()]:
                self.chart_stock_combo.setCurrentText(current_stock)
            elif self.prediction_results:
                # 选择第一个有预测结果的股票
                first_stock = list(self.prediction_results.keys())[0]
                self.chart_stock_combo.setCurrentText(str(first_stock))
            
        except Exception as e:
            print(f"更新图表股票选择器失败: {str(e)}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    
    # 设置应用程序信息
    app.setApplicationName("股票数据分析可视化系统")
    app.setApplicationVersion("1.0")
    
    # 创建主窗口
    window = UnifiedStockAnalysisApp()
    window.show()
    
    # 启动应用
    sys.exit(app.exec_())