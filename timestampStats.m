cd Results/
tsWithout_filename = ls ("*Wo.csv");
tsWithout_filename = tsWithout_filename(1:end-1);

tsWith_filename = ls ("*With.csv");
tsWith_filename = tsWith_filename(1:end-1);

withVector = load(tsWith_filename);

withoutVector = load(tsWithout_filename);


withVector_ms = withVector*1000;
withoutVector_ms = withoutVector*1000;

timestamp_stats = zeros(2,5);
% first row: statistics without timestamps
% second row: statistics with timestamps
timestamp_stats(1,1) = mean(withoutVector_ms);
timestamp_stats(1,2) = std(withoutVector_ms);
timestamp_stats(1,3) = median(withoutVector_ms);
timestamp_stats(1,4) = max(withoutVector_ms);
timestamp_stats(1,5) = min(withoutVector_ms);
timestamp_stats(1,6) = sum(withoutVector_ms); %total time error

timestamp_stats(2,1) = mean(withVector_ms);
timestamp_stats(2,2) = std(withVector_ms);
timestamp_stats(2,3) = median(withVector_ms);
timestamp_stats(2,4) = max(withVector_ms);
timestamp_stats(2,5) = min(withVector_ms);
timestamp_stats(2,6) = sum(withVector_ms); %total time error

% sample = rand(2,5);
rowNames = {'Without timestamps','With timestamps'};
colNames = {'Mean','StandardDeviation','Median','Max','Min','TotalTimeError'};
sTable = array2table(timestamp_stats,'RowNames',rowNames,'VariableNames',colNames);

save("res_labels.mat","sTable")

cd ..