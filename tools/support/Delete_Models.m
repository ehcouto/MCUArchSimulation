function Delete_Models( modelNames )
%Delete_Models deletes all the models in the cell array 'modelNames' that
% is provided as input to the function, except for the 1st model in the
% cell array which is usually the new version of the top level model
% created using Replace_Mdlref_SubSys.
% Syntax: Delete_Models( modelNames )

if( ~iscellstr( modelNames ) )
    error( 'Input is not a cell array of strings' );
end;

for k = 2 : length( modelNames )
    if( bdIsLoaded( modelNames{k} ) )
        bdclose( modelNames{k} );
    end;
    
    fileName = which( modelNames{k} );
    delete( fileName );
end;

    