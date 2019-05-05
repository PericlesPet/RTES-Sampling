results_filename = ls ("*.csv")
timeshiftVector = load(results_filename);

timeshiftVector_ms = timeshiftVector*1000;
ts_stats = zeros(5,1);
ts_mean = mean(timeshiftVector);
ts_std = std(timeshiftVector);
ts_max = max(timeshiftVector);
ts_min = max(timeshiftVector);
ts_median = median(timeshiftVector);

sample = rand(2,5);
rowNames = {'without timestamps','with timestamps'};
colNames = {'mean','std','median','max','min'};
sTable = array2table(sample,'RowNames',rowNames,'VariableNames',colNames);

save("res_labels.mat","sTable")
