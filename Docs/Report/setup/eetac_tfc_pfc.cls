%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%                                                                  %%%%% 
%%%%%%            Document d'estil per TFC/PFC de l'EETAC               %%%%% 
%%%%%%                                                                  %%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%         Authr: Xavier Prats i Menéndez (xavier.prats@upc.edu)           %% 
%%                  Technical University of Catalonia (UPC)                %%
%%                                                                         %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%      This work is licensed under the Creative Commons  Attribution-     %%
%%   -Noncommercial-Share Alike 3.0 Spain License. To view a copy of this  %% 
%%    license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/es/  %%
%%    or send a letter to Creative Commons, 171 Second Street, Suite 300,  %%
%%                  San Francisco,California, 94105, USA.                  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Versió 2.1 - Juliol 2012                                                %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%----------------------------------------------------------------------------------------%%%
%%%                                  IDENTIFICATION                                        %%%
%%%----------------------------------------------------------------------------------------%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{eetac_tfc_pfc}
              [2012/07/01 v2.1 EETAC TFC/PFC document style]

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%----------------------------------------------------------------------------------------%%%
%%%                                 INITIAL CODE                                           %%%
%%%----------------------------------------------------------------------------------------%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\RequirePackage{ifthen}

\newboolean{twoside}     
\newboolean{mparswitch}
\newboolean{@draft}      \setboolean{@draft}{false}
\newboolean{@final}      \setboolean{@final}{false}

\newboolean{Lcat}        \setboolean{Lcat}{true}
\newboolean{Leng}        \setboolean{Leng}{false}
\newboolean{PFC}         \setboolean{PFC}{false}
\newboolean{UNautor}     \setboolean{UNautor}{false}
\newboolean{UNdirector}  \setboolean{UNdirector}{false}
\newboolean{supervisor}  \setboolean{supervisor}{false}
\newboolean{logo}        \setboolean{logo}{false}
\newboolean{paginaLOF}   \setboolean{paginaLOF}{true}
\newboolean{paginaLOT}   \setboolean{paginaLOT}{true}
\newboolean{dedicatoria} \setboolean{dedicatoria}{false}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%----------------------------------------------------------------------------------------%%%
%%%                        OPTIONS DECLARATION and EXECUTION                               %%%
%%%----------------------------------------------------------------------------------------%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\DeclareOption{oneside}{\setboolean{twoside}{false} \setboolean{mparswitch}{false}}
\DeclareOption{twoside}{\setboolean{twoside}{true} \setboolean{mparswitch}{true}}

\DeclareOption{draft}{\AtEndOfClass{\setlength\overfullrule{10pt}\setboolean{@draft}{true}}}
\DeclareOption{final}{\AtEndOfClass{\setlength\overfullrule{0pt} \setboolean{@final}{true}}}

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{book}}
%\DeclareOption*{code}  -->  code execution for a unknown option
%\PassOptionsToPackage{option}{pack}
%\CurrentOption

%% EXECUTION OF OPTIONS
% default options if not specified 
\ExecuteOptions{twoside,final}  
\ProcessOptions

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%----------------------------------------------------------------------------------------%%%
%%%                                 PACKAGE LOADING                                        %%%
%%%----------------------------------------------------------------------------------------%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\LoadClass[a4paper,12pt]{book}
%\LoadClass{book}

%%% FancyHeadings, nextpage, calc, praphics packages are required
\RequirePackage{calc}                %% Allows basic operations inside LaTeX commands
\RequirePackage{helvet}              %% Set the default font family
\RequirePackage{pslatex}             %% Arialfont 
\RequirePackage{fancyhdr,nextpage}   %% Fancy Headers. Next page can force empty style when  
                                     %% blank page is inserted due to chapter change        
                                     %% by using \cleartooddpage instead of \cleardoublepage

\RequirePackage[subfigure]{tocloft}  %% Controls typografic design of the TOC, LOF etc...
\RequirePackage{graphicx}            %% Include graphic files
\RequirePackage{url}                 %% Allows a easy handle of URLs
                                     %% (very helpful in the bibliography!)


\renewcommand{\familydefault}{\sfdefault}  %% sans-serif is default
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%----------------------------------------------------------------------------------------%%%
%%%                              DOCUMENT CLASS DEFINITIONS                                %%%
%%%----------------------------------------------------------------------------------------%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%\ifthenelse{test}{thencode}{elsecode}
%%\equal{string1}{string2}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% PAGE LAYOUT                                                                              %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% NOTE!!: All margin dimensions are measured from a point one inch
% from top and side of page.  

% HORIZONTAL SPACING
%%%%%%%%%%%%%%%%%%%%

\ifthenelse{\boolean{twoside}}{% Values for two-sided printing:
  \setlength{\oddsidemargin}{0.46cm}      %   Left margin on odd-numbered pages.
  \setlength{\evensidemargin}{0.46cm}     %   Left margin on even-numbered pages.
  \setlength{\marginparwidth}{0cm}        %   Width of marginal notes.
  \setlength{\marginparsep}{0pt}            % Horizontal space between outer margin and marginal note
}
{% Values for one-sided printing:
  \setlength{\oddsidemargin}{0.46cm}      %   Left margin on odd-numbered pages.
  \setlength{\evensidemargin}{0.46}       %   Left margin on even-numbered pages.
  \setlength{\marginparwidth}{0cm}        %   Width of marginal notes.
  \setlength{\marginparsep}{0pt}            % Horizontal space between outer margin and marginal note
}
%\setlength{\hoffset}{-1cm}

% VERTICAL SPACING
%%%%%%%%%%%%%%%%%%
% Top of page:
\setlength{\headheight}{1\baselineskip + 0.1pt}  %    Height of box containing running head.
\setlength{\headsep}{8mm}                %    Space between running head and text.
\setlength{\topmargin}{-0.04cm - \headheight - \headsep}          
                                         %    Nominal distance from top of page to top of box containing running head.
% Bottom of page:
\setlength{\footskip}{7mm}       %    Distance from baseline of box containing foot to baseline of last line of text.

% DIMENSION OF TEXT
%%%%%%%%%%%%%%%%%%%

\setlength{\textheight}{24.6cm}    % \textheight is the height of text 
                                   %(including footnotes and figures, excluding running head and foot).
\setlength{\textwidth}{15cm}       % Width of text line.

% A \raggedbottom command causes 'ragged bottom' pages: pages set to
% natural height instead of being stretched to exactly \textheight.
\raggedbottom

% FOOTNOTES
%%%%%%%%%%%
\setlength{\footnotesep}{8.4pt}    % Height of strut placed at the beginning of every footnote = 
                                   % height of normal \footnotesize strut, so no extra space between footnotes.
%%\skip\footins 10.8pt plus 4pt minus 2pt  % Space between last line of text and 
                                         % top of first footnote.

% FLOATS: (a float is something like a figure or table)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% FOR FLOATS ON A TEXT PAGE
%    ONE-COLUMN MODE OR SINGLE-COLUMN FLOATS IN TWO-COLUMN MODE:
\setlength{\floatsep}{14pt plus 2pt minus 4pt}     % Space between adjacent floats moved  to top or bottom of text page.
\setlength{\textfloatsep}{20pt plus 2pt minus 4pt} % Space between main text and floats at top or bottom of page.
\setlength{\intextsep}{14pt plus 4pt minus 4pt}    % Space between in-text figures and text
%    TWO-COLUMN FLOATS IN TWO-COLUMN MODE:
\setlength{\dblfloatsep}{14pt plus 2pt minus 4pt}  % Same as \floatsep for double-column figures in two-column mode.
\setlength{\dbltextfloatsep}{20pt plus 2pt minus 4pt}% \textfloatsep for double-column floats.


%  FOR FLOATS ON A SEPARATE FLOAT PAGE OR COLUMN
%    ONE-COLUMN MODE OR SINGLE-COLUMN FLOATS IN TWO-COLUMN MODE:
\setlength{\@fptop}{0pt plus 1fil}      % Stretch at top of float page/column. (Must be 0pt plus ...)          
\setlength{\@fpsep}{10pt plus 2fil}     % Space between floats on float page/column.       
\setlength{\@fpbot}{0pt plus 1fil}      % Stretch at bottom of float page/column. (Must be 0pt plus ... )    
%   DOUBLE-COLUMN FLOATS IN TWO-COLUMN MODE.
\setlength{\@dblfptop}{0pt plus 1fil}   % Stretch at top of float page. (Must be 0pt plus ...)
\setlength{\@dblfpsep}{10pt plus 2fil}  % Space between floats on float page.
\setlength{\@dblfpbot}{0pt plus 1fil}   % Stretch at bottom of float page. (Must be 0pt plus ... )     

% MARGINAL NOTES
%%%%%%%%%%%%%%%%
\setlength{\marginparpush}{7pt}       % Minimum vertical separation between two marginal notes.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% NEW ENVIRONMENT DEFINITIONS                                                              %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\newlength{\logoEPSCheight}   
\setlength{\logoEPSCheight}{1.5cm}
\newsavebox{\logoEPSC}
\sbox{\logoEPSC}{\includegraphics[totalheight=\logoEPSCheight]{./setup/EETAC-positiu-negre}}

\newcommand{\mylogo}[2]{ 
  \newlength{\logoheight} 
  \newsavebox{\logo}      
  \setlength{\logoheight}{#2}
  \sbox{\logo}{\includegraphics[totalheight=\logoheight]{#1}}
}



\newcommand{\@textDedicatoria}{Falta dedicatoria!}
\newcommand{\textDedicatoria}[1]{\renewcommand{\@textDedicatoria}{#1}}
\newcommand{\@titol}{Falta titol!}
\newcommand{\titol}[1]{\renewcommand{\@titol}{#1}}
\newcommand{\@titolE}{Falta titol Angles!}
\newcommand{\titolE}[1]{\renewcommand{\@titolE}{#1}}
\newcommand{\@titolC}{Falta titol Catala!}
\newcommand{\titolC}[1]{\renewcommand{\@titolC}{#1}}
\newcommand{\@autor}{Falta autor!}
\newcommand{\autor}[1]{\renewcommand{\@autor}{#1}}
\newcommand{\@director}{Falta director!}
\newcommand{\director}[1]{\renewcommand{\@director}{#1}}
\newcommand{\@segondirector}{Falta segon director!}
\newcommand{\segonDirector}[1]{\renewcommand{\@segondirector}{#1}}
\newcommand{\@supervisor}{Falta supervisor!}
\newcommand{\supervisor}[1]{\renewcommand{\@supervisor}{#1}}
\newcommand{\@titulacio}{Falta titulacio!}
\newcommand{\titulacio}[1]{\renewcommand{\@titulacio}{#1}}

\newlength{\Lautors}
\newlength{\Ldirectors}

%% PORTADA ENVIRONMENT
%%%%%%%%%%%%%%%%%%%%%%
\newcommand{\portada}{
  \ifthenelse{\boolean{Leng}}{
    %\newcommand{\@NtitolPFC}{PFC title}
    %\newcommand{\@NtitolTFC}{TFC title}
    % Modificació respecte a la versió 2.1 - Iván Padilla Montero - Juliol 2014
    \newcommand{\@NtitolTFC}{TFG title}
    \newcommand{\@Ntitulacio}{Degree}
    \newcommand{\@Nautor}{Author}
    \newcommand{\@Nautors}{Authors}
    \newcommand{\@Ndirector}{Advisor}
    \newcommand{\@Ndirectors}{Advisors}
    \newcommand{\@Nsupervisor}{Supervisor}
    \newcommand{\@Ndata}{Date}
    \newcommand{\@Napp}{Appendices}
  }{
    \ifthenelse{\boolean{Lcat}}{
      %\newcommand{\@NtitolPFC}{T\'itol del PFC}
      %\newcommand{\@NtitolTFC}{T\'itol del TFC}
      % Modificació respecte a la versió 2.1 - Iván Padilla Montero - Juliol 2014
      \newcommand{\@NtitolTFC}{T\'itol del TFG}
      \newcommand{\@Ntitulacio}{Titulaci\'o}
      \newcommand{\@Nautor}{Autor}
      \newcommand{\@Nautors}{Autors}
      \newcommand{\@Ndirector}{Director}
      \newcommand{\@Ndirectors}{Directors}
      \newcommand{\@Nsupervisor}{Supervisor}
      \newcommand{\@Ndata}{Data}
      \newcommand{\@Napp}{Ap\`endixs}
    }{
      %\newcommand{\@NtitolPFC}{T\'itulo del PFC}
      %\newcommand{\@NtitolTFC}{T\'itulo del TFC}
      % Modificació respecte a la versió 2.1 - Iván Padilla Montero - Juliol 2014
      \newcommand{\@NtitolTFC}{T\'itulo del TFG}
      \newcommand{\@Ntitulacio}{Titulaci\'on}
      \newcommand{\@Nautor}{Autor}
      \newcommand{\@Nautors}{Autores}
      \newcommand{\@Ndirector}{Director}
      \newcommand{\@Ndirectors}{Directores}
      \newcommand{\@Nsupervisor}{Supervisor}
      \newcommand{\@Ndata}{Fecha}    
      \newcommand{\@Napp}{Ap\'endices}                      
    }
  }


  \settowidth{\Lautors}{{\normalsize\bf\sffamily\MakeUppercase   \@Nautors : }}
  \settowidth{\Ldirectors}{{\normalsize\bf\sffamily\MakeUppercase \@Ndirectors :}}
    \renewcommand{\and}{\\ \hspace*{\Lautors}}

  \begin{tabular}{p{\textwidth}}
    \ifthenelse{\boolean{logo}}{\usebox{\logoEPSC}  \hfill \usebox{\logo}   \\[8cm]}{\usebox{\logoEPSC} \\[8cm]}
    \ifthenelse{\boolean{PFC}}{\begin{center}\Huge\sffamily\bfseries  PROJECTE DE FI DE CARRERA \end{center}  \\[5cm]}
                              %{\begin{center}\Huge\sffamily\bfseries  TREBALL DE FI DE CARRERA  \end{center}  \\[5cm]}
                              % Modificació respecte a la versió 2.1 - Iván Padilla Montero - Juliol 2014
                              {\begin{center}\Huge\sffamily\bfseries  TREBALL DE FI DE GRAU  \end{center}  \\[5cm]}
                              
    \fbox{\parbox{\textwidth}{
        \vspace{2ex}
        \ifthenelse{\boolean{PFC}}{{\normalsize\bf\sffamily\MakeUppercase \@NtitolPFC : \@titol}  \\[2ex]}
                                  {{\normalsize\bf\sffamily\MakeUppercase \@NtitolTFC : \@titol}  \\[2ex]}
                   {\normalsize\bf\sffamily\MakeUppercase   \@Ntitulacio : \@titulacio    }  \\[2ex]
                   \ifthenelse{\boolean{UNautor}}{{\normalsize\bf\sffamily\MakeUppercase \@Nautor :  \@autor  } \\[2ex]}
                                                 {{\normalsize\bf\sffamily\MakeUppercase \@Nautors : \@autor  } \\[2ex]}
                   \ifthenelse{\boolean{UNdirector}}{{\normalsize\bf\sffamily\MakeUppercase  \@Ndirector :  \@director }  \\[2ex]}
                                                    {{\normalsize\bf\sffamily\MakeUppercase  \@Ndirectors : \@director \\ \hspace*{\Ldirectors} \@segondirector }  \\[2ex]}
                              \ifthenelse{\boolean{supervisor}}{{\normalsize\bf\sffamily\MakeUppercase  \@Nsupervisor : \@supervisor  } \\[2ex]}{}
                                         {\normalsize\bf\sffamily\MakeUppercase  \@Ndata : \today               }  \\[2ex]
    }} \\
    
  \end{tabular}
  \cleardoublepage
}


%% RESUM ENVIRONMENT
%%%%%%%%%%%%%%%%%%%%%%
\newenvironment{resum}[1]{
  
  \ifthenelse{\boolean{Lcat}}{
    \newcommand{\@NResum}{Resum}
    \newcommand{\@NtitolResum}{T\'itol}
    \newcommand{\@NautorResum}{Autor}
    \newcommand{\@NautorsResum}{Autors}
    \newcommand{\@NdirectorResum}{Director}
    \newcommand{\@NdirectorsResum}{Directors}
    \newcommand{\@NsupervisorResum}{Supervisor}
    \newcommand{\@NdataResum}{Data}
  }{
    \newcommand{\@NResum}{Resumen}
    \newcommand{\@NtitolResum}{T\'itulo}
    \newcommand{\@NautorResum}{Autor}
    \newcommand{\@NautorsResum}{Autores}
    \newcommand{\@NdirectorResum}{Director}
    \newcommand{\@NdirectorsResum}{Directores}
    \newcommand{\@NsupervisorResum}{Supervisor}
    \newcommand{\@NdataResum}{Fecha}
  }
  
  \settowidth{\Lautors}{{\normalsize\bf\sffamily   \@NautorsResum : }}
  \settowidth{\Ldirectors}{{\normalsize\bf\sffamily \@NdirectorsResum :}}
  \renewcommand{\and}{\\ \hspace*{\Lautors}}

  \newlength{\Hresum}
  \setlength{\Hresum}{#1}

  \begin{center}
    \begin{tabular}{|p{\textwidth}|}
      \hline
      \vspace*{2mm}
      {\bf \@NtitolResum  :}   \@titolC   \\[1ex]
      \ifthenelse{\boolean{UNautor}}{{\bf \@NautorResum:}  \@autor   \\[1ex]}
                                    {{\bf \@NautorsResum :} \@autor   \\[1ex]}
      \ifthenelse{\boolean{UNdirector}}{{\bf \@NdirectorResum:}  \@director \\[1ex]}
                                      {{\bf \@NdirectorsResum:} \@director \\ \hspace*{\Ldirectors} \@segondirector  \\[1ex]}
      \ifthenelse{\boolean{supervisor}}{{\bf \@NsupervisorResum:} \@supervisor   \\[1ex]}{}
      {\bf \@NdataResum:}       \today       \\[3mm]
      \hline
    \end{tabular}
    
    \vspace*{2em}
    
    \raggedright      {\bf \@NResum}

    \vspace*{1ex}
        
    \begin{tabular}{|p{\textwidth}|}
      \hline
      \vspace*{2mm}
}{
      \vspace*{\Hresum} \\
      \hline
    \end{tabular}
  \end{center}
  \cleardoublepage
}

%% OVERVIEW ENVIRONMENT
%%%%%%%%%%%%%%%%%%%%%%%%
\newenvironment{overview}[1]{
  \settowidth{\Lautors}{{\normalsize\bf\sffamily Authors: }}
  \settowidth{\Ldirectors}{{\normalsize\bf\sffamily Advisors:}}
  \renewcommand{\and}{\\ \hspace*{\Lautors}}
  
  \newlength{\Hoverview}
  \setlength{\Hoverview}{#1}
  
  \begin{center}
    \begin{tabular}{|p{\textwidth}|}
      \hline
      \vspace*{2mm}
      {\bf Title :}     \@titolE   \\[1ex]
      \ifthenelse{\boolean{UNautor}}{{\bf Author:}  \@autor  \\[1ex]}
                                    {{\bf Authors:} \@autor  \\[1ex]}
      \ifthenelse{\boolean{UNdirector}}{{\bf Advisor:}  \@director \\[1ex]}
                                       {{\bf Advisors:} \@director \\ \hspace*{\Ldirectors} \@segondirector  \\[1ex]}
      \ifthenelse{\boolean{supervisor}}{{\bf Supervisor:} \@supervisor   \\[1ex]}{}
      {\bf Date:}       \today       \\[3mm]
      \hline
    \end{tabular}
    
    \vspace*{2em}
    
    \raggedright      {\bf Overview}
    
    \vspace*{1ex}
        
    \begin{tabular}{|p{\textwidth}|}
      \hline
      \vspace*{2mm}
}{
      \vspace*{\Hoverview} \\
      \hline
    \end{tabular}
  \end{center}
  \cleardoublepage
}



\newlength{\normalparskip}
\newlength{\normalparindent}
\setlength{\normalparskip}{1ex}
\setlength{\normalparindent}{0ex}
\setlength{\parskip}{\normalparskip}           % Skip size between two paragraphs
\setlength{\parindent}{\normalparindent}       % Indentation for new paragraphs

\newcommand{\beforepreface}{
  \pagestyle{empty}
  \pagenumbering{roman}
  \setlength{\parskip}{0ex}
  \setlength{\parindent}{0ex}
  \portada
}

\newcommand{\afterpreface}{%
  \ifdedicatoria
    \vspace*{5cm}
    \begin{flushright}
      \@textDedicatoria
    \end{flushright}
    \cleartooddpage[\thispagestyle{empty}]  
  \fi
  \tableofcontents
  \cleartooddpage[\thispagestyle{empty}]
  \ifpaginaLOF
%    \addcontentsline{toc}{section}{List of Figures}
    \listoffigures
    \cleartooddpage[\thispagestyle{empty}]
  \fi
  \ifpaginaLOT
%    \addcontentsline{toc}{section}{List of Tables}
  \listoftables 
  \cleartooddpage[\thispagestyle{empty}]
  \fi
  \setlength{\parskip}{\normalparskip}
  \setlength{\parindent}{\normalparindent}
  \cleartooddpage[\thispagestyle{empty}]
  % Define the chapter information (for the header):
  %    \renewcommand{\chaptermark}[1]{\markboth{\sffamily\small\@chapapp{} \thechapter\ - \ ##1}{}}
  % Define the section information (for the header):
%    \renewcommand{\sectionmark}[1]{\markright{\sffamily\small \thesection \ ##1}}
  %    \headingson
  \pagenumbering{arabic}
  \pagestyle{fancy}
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% HEADERS AND FOOTERS DESIGN                                                               %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\renewcommand\headrulewidth{0.5pt}
\renewcommand\footrulewidth{0pt}
%\addtolength{\headwidth}{\marginparwidth+\marginparsep}   % Span headwidth to marginal notes

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% REDEFINITION OF PAGE MARKERS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\renewcommand{\sectionmark}[1]{\markright{#1}}
\renewcommand{\chaptermark}[1]{\markboth{\footnotesize #1}{#1}}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% HEADERS AND FOOTERS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\lhead[\fancyplain{}{\footnotesize \thepage}]{\fancyplain{\leftmark}{\leftmark}}
\chead{}
\rhead[\fancyplain{}{\footnotesize \@titol}]{\fancyplain{}{\footnotesize \thepage}}
\lfoot{}
\cfoot{}
\rfoot{}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% TABLE OF CONTENTS DEFINITION                                                             %%   
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\tocloftpagestyle{empty}
    
%% TOC title configuration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\setlength{\cftbeforetoctitleskip}{0ex}
\setlength{\cftaftertoctitleskip}{0ex}
\renewcommand{\cfttoctitlefont}{\LARGE\sffamily\bfseries\MakeUppercase}
\renewcommand{\cftaftertoctitle}{\\}

%% LOF title configuration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\setlength{\cftbeforeloftitleskip}{0pt}
\setlength{\cftafterloftitleskip}{0ex}
\renewcommand{\cftloftitlefont}{\LARGE\sffamily\bfseries\MakeUppercase}
\renewcommand{\cftafterloftitle}{\\}

%% LOT title configuration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\setlength{\cftbeforelottitleskip}{0pt}
\setlength{\cftafterlottitleskip}{0ex}
\renewcommand{\cftlottitlefont}{\LARGE\sffamily\bfseries\MakeUppercase}
\renewcommand{\cftafterlottitle}{\\}

% TOC chapter configuration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Chapters
\setlength{\cftbeforechapskip}{2em}   
\setlength{\cftchapindent}{0em}
\setlength{\cftchapnumwidth}{7em}
\renewcommand{\cftchapleader}{\bfseries\cftsecleader}
\renewcommand{\cftchapfont}{\large\sffamily\bfseries}
\renewcommand{\cftchappagefont}{\large\sffamily\bfseries} 
\renewcommand{\cftchappresnum}{\MakeUppercase \@chapapp{} \space}%
\renewcommand{\cftchapaftersnum}{. \space}%
%\renewcommand{\cftchapaftersnumb}{}%

%% Sections
\setlength{\cftbeforesecskip}{1em}   
\setlength{\cftsecindent}{0em}
\setlength{\cftsecnumwidth}{2em}
\renewcommand{\cftsecfont}{\normalsize\sffamily\bfseries}
\renewcommand{\cftsecpagefont}{\normalsize\sffamily\bfseries} 
\renewcommand{\cftsecpresnum}{}%
\renewcommand{\cftsecaftersnum}{}%
%\renewcommand{\cftsecaftersnumb}{}%

%% Subsections
\setlength{\cftbeforesubsecskip}{0.2em}   
\setlength{\cftsubsecindent}{3em}
\setlength{\cftsubsecnumwidth}{3em}
\renewcommand{\cftsubsecfont}{\normalsize\sffamily}
\renewcommand{\cftsubsecpagefont}{\normalsize\sffamily} 
\renewcommand{\cftsubsecpresnum}{}%
\renewcommand{\cftsubsecaftersnum}{}%
%\renewcommand{\cftsecaftersnumb}{}%

% Table of figures and table of tables
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\renewcommand{\l@figure}{\@dottedtocline{1}{0em}{2em}}
\renewcommand{\l@table}{\l@figure}

%%%% specifies the highest level appearing in the table of contents
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\setcounter{tocdepth}{2}
%\setcounter{minitocdepth}{4}         % idem for mini table of contents

%%%% configures minitoc font properties
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%\setlength{\mtcindent}{24pt}
%\renewcommand{\mtifont}{\huge\sffamily\bfseries}
%\renewcommand{\mtcfont}{\normalsize\rm}
%\nomtcrule   %%% supress rule in minitoc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% PARAGRAPHING                                                                             %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
\setlength{\parskip}{2ex}          % Extra vertical space between paragraphs (added to \baselineskip)
\setlength{\parindent}{0em}        % Width of paragraph indentation.

\setlength{\topsep}{0.5ex}         % Extra vertical space, in addition to 
                                   % \parskip, added above and below list and
                                   % paragraphing environments.
\setlength{\partopsep}{0.5ex}      % Extra vertical space, in addition to 
                                   % \parskip and \topsep, added when user
                                   % leaves blank line before environment.

\setlength{\itemsep}{1pt}          % Extra vertical space, in addition to 
                                   % \parskip, added between list items.

% The following page-breaking penalties are defined

%\@lowpenalty   51      % Produced by \nopagebreak[1] or \nolinebreak[1]
%\@medpenalty  151      % Produced by \nopagebreak[2] or \nolinebreak[2]
%\@highpenalty 301      % Produced by \nopagebreak[3] or \nolinebreak[3]

%\@beginparpenalty -\@lowpenalty    % Before a list or paragraph environment.
%\@endparpenalty   -\@lowpenalty    % After a list or paragraph environment.
%\@itempenalty     -\@lowpenalty    % Between list items.

% \clubpenalty         % 'Club line'  at bottom of page.
% \widowpenalty        % 'Widow line' at top of page.
% \displaywidowpenalty % Math display widow line.
% \predisplaypenalty   % Breaking before a math display.
% \postdisplaypenalty  % Breaking after a math display.
% \interlinepenalty    % Breaking at a line within a paragraph.
% \brokenpenalty       % Breaking after a hyphenated line.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% HEADINGS OF CHAPTERS AND SECTIONS FORMATTING                                             %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% COUNTER DEFINITIONS
%%%%%%%%%%%%%%%%%%%%%%
%% If you want to redefine an already existing counter use \@addtoreset  command
%
%%%% specifies the highest level with numbered headings
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\setcounter{secnumdepth}{4}

%% CHAPTER HEADINGS
%%%%%%%%%%%%%%%%%%%
% DEFINITION OF THE NUMBERING OF THE HEADERS
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\renewcommand{\thechapter}{\arabic{chapter}}
\renewcommand{\thesection}{\thechapter .\arabic{section}.}
\renewcommand{\thesubsection}{\thesection \arabic{subsection}.}
\renewcommand{\thesubsubsection}{\thesubsection \arabic{subsubsection}.}
\renewcommand{\theparagraph}{\alph{paragraph}}
\renewcommand{\thesubparagraph}{-}

\renewcommand{\chapter}{%
  \if@openright\cleartooddpage[\thispagestyle{empty}]\else\clearpage\fi
  \suppressfloats[t]  % Prevents floats appearing in the top of the page chapter
  \addtocontents{lof}{\protect\addvspace{15\p@}}%
  \addtocontents{lot}{\protect\addvspace{15\p@}}%
  \thispagestyle{plain}
  \global\@topnum\z@
  \@afterindentfalse
  \secdef\@chapter\@schapter
}

% \@makechapterhead Makes the heading for the \chapter command.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\renewcommand{\@makechapterhead}[1]{%
  \noindent                             % No indentation in this paragraph
  \begin{center}                    % Prints chapter name etc...
    \LARGE\sffamily\bfseries\MakeUppercase 
    \@chapapp{} \thechapter . \MakeUppercase{#1} \par\nobreak  %% \@chapapp{} prints ``CHAPTER'' according to selected language
  \end{center}                     
  \vspace{3ex}
}

% \@makechapterhead Makes the heading for the \chapter* command.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\renewcommand{\@makeschapterhead}[1]{%
  \noindent                                                     % No indentation in this paragraph
  \begin{center}
    \LARGE\sffamily\bfseries \MakeUppercase{#1} \par\nobreak
  \end{center}
  \vspace{3ex}
  \addcontentsline{toc}{chapter}{\large\sffamily\bfseries #1}
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% SECTIONS HEADINGS
%%%%%%%%%%%%%%%%%%%%

% \@startsection {NAME}{LEVEL}{INDENT}{BEFORESKIP}{AFTERSKIP}{STYLE} 
%            optional * [ALTHEADING]{HEADING}
%    Generic command to start a section.  
%    NAME       : e.g., 'subsection'
%    LEVEL      : a number, denoting depth of section -- e.g., chapter=1,
%                 section = 2, etc.  A section number will be printed if
%                 and only if LEVEL < or = the value of the secnumdepth
%                 counter.
%    INDENT     : Indentation of heading from left margin
%    BEFORESKIP : Absolute value = skip to leave above the heading.  
%                 If negative, then paragraph indent of text following 
%                 heading is suppressed.
%    AFTERSKIP  : if positive, then skip to leave below heading,
%                       else - skip to leave to right of run-in heading.
%    STYLE      : commands to set heading style 
%  If '*' missing, then increments the counter.  If it is present, then
%  there should be no [ALTHEADING] argument.  A sectioning command
%  is normally defined to \@startsection + its first six arguments.

%% REDEFINITION OF ALREADY EXISTING SECTIONS (book.cls)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\renewcommand{\section}{%
  \@startsection {section}%                          %% NAME
                 {1}{0pt}%                           %% LEVEL and INDENT
                 {-3.5ex plus -1ex minus -.2ex}%    %% BEFORESKIP
                 {2.3ex plus .2ex}%                  %% AFTERSKIP
                 {\sffamily\Large\bfseries}%         %% STYLE
}

\renewcommand{\subsection}{%
  \@startsection{subsection}%                        %% NAME
                {2}{0pt}%                            %% LEVEL and INDENT
                {-3.25ex plus -1ex minus -.2ex}%     %% BEFORESKIP
                {1.5ex plus .2ex}%                   %% AFTERSKIP
                {\sffamily\large\bfseries}%          %% STYLE
}

\renewcommand{\subsubsection}{%
  \@startsection{subsubsection}%                     %% NAME
                {3}{0pt}%                            %% LEVEL and INDENT
                {-3.25ex plus -1ex minus -.2ex}%     %% BEFORESKIP
                {1.0ex plus .2ex}%                   %% AFTERSKIP
                {\sffamily\normalsize\itshape}%      %% STYLE
}

\renewcommand{\paragraph}{%
  \@startsection{paragraph}%                             %% NAME
                {4}{2ex}%                                %% LEVEL and INDENT
                {3.25ex plus 1ex minus .2ex}%            %% BEFORESKIP
                {1ex}%                                   %% AFTERSKIP
                {\normalsize\bfseries} %        %% STYLE
}

\renewcommand{\subparagraph}{%
  \@startsection{subparagraph}%                      %% NAME
                {5}{3ex}%                            %% LEVEL and INDENT
                {3.25ex plus 1ex minus .2ex}%        %% BEFORESKIP
                {1ex}%                              %% AFTERSKIP
                {\normalsize\bfseries}%                       %% STYLE
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% APPENDICES CONFIGURATION
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\DeclareRobustCommand{\changetoapp}{%
  \setlength{\cftbeforechapskip}{2em}  
  \setlength{\cftchapindent}{0em}
  \setlength{\cftchapnumwidth}{8em}
  \renewcommand{\cftchapleader}{\bfseries\cftsecleader}
  \renewcommand{\cftchapfont}{\large\sffamily\bfseries}
  \renewcommand*{\cftchappresnum}{\MakeUppercase \appendixname \space}%
  \renewcommand{\cftchapaftersnum}{. \space}
  \renewcommand{\cftchapaftersnumb}{}%
}

\let\oldappendix\appendix

\renewcommand*{\appendix}{
  \oldappendix 
  \addtocontents{toc}{\changetoapp}
 % \addtocontents{toc}{\protect\clearpage\par}
%  \addtocontents{toc}{{\Large\sffamily\bfseries Annexos}\par}
%  \addtocontents{toc}{\protect\apprule \par}
  
  \addtocontents{lof}{\changetoapp}
%  \addtocontents{lof}{\protect\clearpage\par}
%  \addtocontents{lof}{{\Large\sffamily\bfseries Annexos}\par}
 % \addtocontents{lof}{\protect\apprule \par}

  \addtocontents{lot}{\changetoapp} 
%  \addtocontents{lot}{\protect\clearpage\par}
%  \addtocontents{lot}{{\Large\sffamily\bfseries Annexos}\par}
%  \addtocontents{lot}{\protect\apprule \par}


  \cleardoublepage
  
}

\newcommand{\senseportada}{
  \vspace*{\stretch{1}}                
  \begin{center}                    % Prints chapter name etc...
    \Huge\sffamily\bfseries\MakeUppercase \@Napp  \par
  \end{center}                     
  \vspace*{\stretch{2}}                
  \thispagestyle{empty}                 % Page style
  \newpage
  \thispagestyle{empty}                 % Page style
  \newpage
}

\newcommand{\ambportada}{
  \settowidth{\Lautors}{{\normalsize\bf\sffamily\MakeUppercase   \@Nautors : }}
  \settowidth{\Ldirectors}{{\normalsize\bf\sffamily\MakeUppercase \@Ndirectors :}}

  \begin{tabular}{p{\textwidth}}
    \ifthenelse{\boolean{logo}}{\usebox{\logoEPSC}  \hfill \usebox{\logo}   \\[8cm]}{\usebox{\logoEPSC} \\[8cm]}
    \begin{center}\Huge\sffamily\bfseries\MakeUppercase  \@Napp \end{center}  \\[5cm]
    \fbox{\parbox{\textwidth}{
        \vspace{2ex}
        \ifthenelse{\boolean{PFC}}{{\normalsize\bf\sffamily\MakeUppercase \@NtitolPFC : \@titol  } \\[2ex]}
                   {{\normalsize\bf\sffamily\MakeUppercase \@NtitolTFC  : \@titol  } \\[2ex]}
                   {\normalsize\bf\sffamily\MakeUppercase  \@Ntitulacio : \@titulacio    }  \\[2ex]
                   \ifthenelse{\boolean{UNautor}}{{\normalsize\bf\sffamily\MakeUppercase \@Nautor:  \@autor } \\[2ex]}
                              {{\normalsize\bf\sffamily\MakeUppercase \@Nautors : \@autor } \\[2ex]}
                              \ifthenelse{\boolean{UNdirector}}{{\normalsize\bf\sffamily\MakeUppercase \@Ndirector :  \@director }  \\[2ex]}
                                         {{\normalsize\bf\sffamily\MakeUppercase \@Ndirectors : \@director \\ \hspace*{\Ldirectors} \@segondirector }  \\[2ex]}
                                         \ifthenelse{\boolean{supervisor}}{{\normalsize\bf\sffamily\MakeUppercase \@Nsupervisor : \@supervisor  } \\[2ex]}{}
                                                    {\normalsize\bf\sffamily\MakeUppercase  \@Ndata : \today               }  \\[2ex]
    }} \\
  \end{tabular}
  \setcounter{page}{-1}
}
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%----------------------------------------------------------------------------------------%%%
%%%----------------------------   END OF CLASS FILE  --------------------------------------%%%
%%%----------------------------------------------------------------------------------------%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

