for i=1:3
    for j=1:4
        c(i,j)=(i-1) * 4 + (j-1);
    end
end

disp('c在matlab中的输出为:');
disp(c);

%调用C语言程序
output_cc = matrix_demo(c);

disp('output_cc在matlab中的输出为:');
disp(output_cc);

% clearvars
