library(ggplot2)
# 讀取數據
data <- read.csv("C:\\C\\NCKU\\HW10\\time_table.csv")

# 插入操作的折線圖
ggplot(data, aes(x = cycle_insert, y = frequency_i)) +
  geom_line(color = "blue", size = 1) +
  geom_point(color = "blue") +
  labs(x = "cycle_insert", y = "frequency") +
  theme_minimal()
print(sum(data$cycle_insert*data$frequency_i, na.rm = TRUE)/sum(data$frequency_i, na.rm = TRUE))

# 刪除操作的折線圖
ggplot(data, aes(x = cycle_delete, y = frequency_d)) +
  geom_line(color = "red", size = 1) +
  geom_point(color = "red") +
  labs(x = "cycle_delete", y = "frequency") +
  theme_minimal()
print(sum(data$cycle_delete*data$frequency_d, na.rm = TRUE)/sum(data$frequency_d, na.rm = TRUE))

# 搜索操作的折線圖
ggplot(data, aes(x = cycle_search, y = frequency_s)) +
  geom_line(color = "green", size = 1) +
  geom_point(color = "green") +
  labs(x = "cycle_search", y = " frequency") +
  theme_minimal()
print(sum(data$cycle_search*data$frequency_s, na.rm = TRUE)/sum(data$frequency_s, na.rm = TRUE))
