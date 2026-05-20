function test_runner(prms)
    coverage_mode = prms.coverage;
    testing_mode = prms.testing;
    log_mode = prms.log;
    main_sim = prms.main_sim;
    
    [~,~] = mkdir('test_results');
    
    if (log_mode == 1)
        if exist(fullfile(pwd, 'test_results/log.txt'), 'file') == 2
            delete('test_results/log.txt');
        end
        diary('test_results/log.txt');
    end

    openProject('.');
    compile;


    if (testing_mode == 1)
        import matlab.unittest.TestRunner;
        import matlab.unittest.Verbosity;
        import matlab.unittest.plugins.TAPPlugin;
        import matlab.unittest.plugins.ToFile;
        import matlab.unittest.plugins.XMLPlugin;
        
        
        suite = testsuite(pwd, 'IncludeSubfolders', true);
        
    
        if (coverage_mode == 1)
            if ~isempty(dir('test_results\cov_report\*.html'))
                rmdir('test_results\cov_report')
            end
            mkdir('test_results\cov_report');
        end
        
        if exist(fullfile(pwd, 'test_results/taptestresults.tap'), 'file') == 2
            delete('test_results/taptestresults.tap');
        end
        
        runner = TestRunner.withTextOutput('OutputDetail', Verbosity.Detailed);
        runner.addPlugin(TAPPlugin.producingVersion13(ToFile('test_results/taptestresults.tap')));
        runner.addPlugin(XMLPlugin.producingJUnitFormat('test_results/junittestresults.xml'));
        try
            %runner.addModelCoverage("cobertura", "test_results/coverage.xml");
            runner.addModelCoverage("html-report","test_results/cov_report");
        catch ME
            warning(ME.message)
            warning('Skipping Coverage info!')
        end
    
        results = runner.run(suite);
        
%         nfailed = nnz([results.Failed]);
%         try
%             assert(nfailed == 0, [num2str(nfailed) ' test(s) failed.']);
%         catch ME
%             disp(ME.message)
%             error('Build marked as UNSTABLE')
%         end
    else
        % just run the simulation to see if it runs without errors
        eval(['sim ' main_sim]);
    end
    diary OFF;