%% Import data from spreadsheet
% Script for importing data from the following spreadsheet:
%
%    Workbook: /Users/mariaguramare/neuro_140/project/prot_data/rhinoviruses/coords/rhinoviruses_coords.xlsx
%    Worksheet: 1 sheet per protein
%
% To extend the code for use with different selected data or a different
% spreadsheet, generate a function instead of a script.

%% For each sheet
ks = zeros(35, 1);
avs = zeros(35, 1);
for i = 1:35

%% Import the data
sheet_name = strcat('Sheet', string(i));
[~, ~, raw] = xlsread('/Users/mariaguramare/neuro_140/project/prot_data/rhinoviruses/coords/rhinoviruses_coords.xlsx',sheet_name);
raw(cellfun(@(x) ~isempty(x) && isnumeric(x) && isnan(x),raw)) = {''};

%% Replace non-numeric cells with NaN
R = cellfun(@(x) ~isnumeric(x) && ~islogical(x),raw); % Find non-numeric cells
raw(R) = {0}; % Replace non-numeric cells

%% Create output variable
data = reshape([raw{:}],size(raw));

%% Create table
P1 = table;

%% Allocate imported array to column variable names
P1.X = data(:,1);
P1.Y = data(:,2);
P1.Z = data(:,3);

%% Compute Convex Hull & Volume
[k, av] = convhull(P1.X, P1.Y, P1.Z,'Simplify',true);
[m, n] = size(k);
[p, q] = size(P1.X);
percent_ch_points = m/p;
ks(i) = percent_ch_points;
avs(i) = av;
display(percent_ch_points)
display(av)

%% Clear temporary variables
clearvars data raw R;

end